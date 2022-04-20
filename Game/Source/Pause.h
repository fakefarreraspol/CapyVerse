#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "GuiText.h"

#include "List.h"


struct SDL_Texture;

class Pause : public Module
{
public:

	Pause(bool startEnabled);

	// Destructor
	virtual ~Pause();

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
	List<GuiControl*> optionsBtns;
	List<GuiControl*> exitBtns;

	List<GuiControl*> currentControls;

	GuiButton* optionsBtn;
	GuiButton* volumeBtn;
	GuiSlider* musicSldr;
	GuiSlider* soundSlrd;
	GuiCheckBox* fullscreenChkbx;
	GuiCheckBox* vsyncChkbx;
	GuiButton* returnOPBtn;


	GuiButton* exitBtn;
	GuiButton* yesBtn;
	GuiButton* noBtn;
	GuiText* exitText;

	ListItem<GuiControl*>* currentControl;

	GuiText* pauseText;

	SDL_Texture* arrow = nullptr;

};
#endif // __PAUSE_H__