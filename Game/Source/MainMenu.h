#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "GuiText.h"

#include "Timer.h"

#include "List.h"


struct SDL_Texture;

class MainMenu : public Module
{
public:

	MainMenu(bool startEnabled);

	// Destructor
	virtual ~MainMenu();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void DrawMenu();

	void UpdateInput();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	SDL_Texture* background = nullptr;
	
	List<GuiControl*> menuBtns;
	List<GuiControl*> playBtns;
	List<GuiControl*> optionsBtns;
	List<GuiControl*> exitBtns;


	GuiButton* playBtn;
	GuiButton* newGameBtn;
	GuiButton* continueBtn;
	GuiButton* returnPlBtn;
	
	GuiButton* optionsBtn;
	GuiButton* volumeBtn;
	GuiSlider* musicSldr;
	GuiSlider* soundSlrd;
	GuiCheckBox* fullscreenChkbx;
	GuiCheckBox* vsyncChkbx;
	GuiButton* returnOPBtn;

	GuiButton* creditsBtn;
	SDL_Texture* creditsText;

	GuiButton* exitBtn;
	GuiButton* yesBtn;
	GuiButton* noBtn;
	GuiText* exitText;
	
	List<GuiText*> credits;

	SDL_Texture* arrow = nullptr;
	SDL_Texture* menus = nullptr;
	SDL_Texture* title = nullptr;
	Timer time;
	bool sound = true;
	bool optionsB = false;
	bool creditsB = false;
	bool exit = false;
	bool play = false;
	int titleSFX;

	int currentTime = 0;
	int duration = 200;
	int startPositionY = -150;
	int finalPositionY = 0;
	int currentPositionY = startPositionY;
};
#endif // __MAINMENU_H__