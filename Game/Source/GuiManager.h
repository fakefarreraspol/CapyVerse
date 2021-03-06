#pragma once

#include "Module.h"
#include "GuiControl.h"

#include "List.h"

class GuiManager : public Module
{
public:

	GuiManager(bool startEnabled);				// Constructor
	virtual ~GuiManager();		// Destructor

	bool Start();
	bool Update(float dt);
	bool UpdateAll(float dt, bool logic);
	bool PostUpdate();
	bool Draw();
	bool SetActiveControll(GuiControl* active);
	const GuiControl* GetActiveControll();

	bool CleanUp();

	// Additional methods
	GuiControl* CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, SDL_Color textColor = {255, 255, 255, 1}, int textID = 0, bool blink = false);
	void DestroyGuiControl(GuiControl* entity);
	void AddGuiControl(GuiControl* entity);

public:

	List<GuiControl*> controls;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	SDL_Texture* buttons = nullptr;
	SDL_Texture* checkbox = nullptr;

private:
	GuiControl* activeControl = nullptr;
};

