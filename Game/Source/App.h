#ifndef __APP_H__
#define __APP_H__

#include "PerfTimer.h"
#include "List.h"
#include "Timer.h"

#include "Module.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"


// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Intro;
class MainMenu;
class Scene;
class EntityManager;
class BattleManager;
class GuiManager;
class DialogManager;
class StatsMenu;
class Physics;
class Task;
class FadeToBlack;
class Fonts;
class Pause;
class BattleScene1;
class BattleScene2;
class BattleScene3;
class EOBScene;
class Map;
class Transitions;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	bool GetDebug();
	void SetDebug(bool value);

	void LoadGameRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:
	// Settings
	bool pause = false;
	// Modules
	Window* win = nullptr;
	Input* input = nullptr;
	Render* render = nullptr;
	Transitions* transitions = nullptr;
	Textures* tex = nullptr;
	Audio* audio = nullptr;
	Intro* intro = nullptr;
	MainMenu* mainMenu = nullptr;
	Scene* scene = nullptr;
	EntityManager* entMan = nullptr;
	Fonts* fonts = nullptr;
	GuiManager* guiManager = nullptr;
	StatsMenu* statsMenu = nullptr;
	Map* mapManager = nullptr;
	DialogManager* dialogManager = nullptr;
	Physics* colManager = nullptr;
	Task* taskManager = nullptr;

	Pause* pauseMenu = nullptr;
	FadeToBlack* fadeToBlack = nullptr;
	BattleManager* battleManager = nullptr;
	BattleScene1* battleScene1 = nullptr;
	BattleScene2* battleScene2 = nullptr;
	BattleScene3* battleScene3 = nullptr;
	EOBScene* eobScene = nullptr;

	bool fpsCap = false;
	float dt = 0.0f;
	uint32 framesPerSecond = 0;
private:
	bool debug = false;

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module*> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	pugi::xml_document configFile;
	pugi::xml_document gameStateFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;

	// L02: DONE 1: Create variables to control when to execute the request load / save
	mutable bool saveGameRequested;
	bool loadGameRequested;



	PerfTimer* ptimer;
	PerfTimer* frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;

	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;


	uint32 maxFrameRate = 0;
};

extern App* app;

#endif	// __APP_H__