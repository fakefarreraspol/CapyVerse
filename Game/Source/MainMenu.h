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

	List<GuiControl*> currentControls;

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
	
	ListItem<GuiControl*>* currentControl;
	
	List<GuiText*> credits;

	SDL_Texture* arrow = nullptr;
	SDL_Texture* title = nullptr;
	Timer time;
	bool sound = true;
	int titleSFX;
};
#endif // __MAINMENU_H__