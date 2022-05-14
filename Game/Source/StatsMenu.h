#ifndef __STATS_MENU_H__
#define __STATS_MENU_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "GuiText.h"

#include "Timer.h"
#include "List.h"

class StatsMenu : public Module
{
public:

	StatsMenu(bool startEnabled);
	virtual ~StatsMenu();

	bool Awake(pugi::xml_node&);
	bool Start();


	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool ActivateMenu();

private:

	List<GuiControl*> menuBtns;
	List<GuiControl*> itemsBtns;
	List<GuiControl*> capyBtns;
	List<GuiControl*> teamBtns;

	List<GuiControl*> currentControls;

	int selectorOffset;

	SDL_Rect menuBounds = {75,290,188,230};
	SDL_Rect itemsBounds = {338, 200, 500, 500};
	SDL_Rect capyBounds;
	SDL_Rect teamBounds;

	ListItem<GuiControl*>* currentControl;
	SDL_Texture* arrow = nullptr;
	SDL_Texture* menus = nullptr;
	SDL_Texture* title = nullptr;

};


#endif // !__ITEM_MENU_H__
