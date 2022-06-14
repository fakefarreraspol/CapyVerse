#ifndef __STATS_MENU_H__
#define __STATS_MENU_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "GuiText.h"

#include "Timer.h"
#include "List.h"

class Capybara;
class Item;

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
	bool LoadCapys(List<GuiControl*>* menu, SDL_Rect bounds, int idStart);
	bool LoadTeam(List<GuiControl*>* menu, SDL_Rect bounds, int idStart);
	bool LoadItems(List<GuiControl*>* menu, SDL_Rect bounds, int idStart);

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool ActivateMenu();
	bool HideMenus();
	bool ClearMenu(List<GuiControl*> *menu);

public:
	List<GuiControl*> mainMenu;

private:

	List<GuiControl*>* currentMenu;

	List<GuiControl*> subMenu;			// 2
	List<GuiControl*> actionsMenu;		// 3
	List<GuiControl*> optionsMenu;		// 4
	int lastMain;
	int lastSub;
	int lastActions;
	int lastOptions;

	// details buttons

	List<GuiControl*> stats;
	List<GuiControl*> statsValue;
	List<GuiControl*> equipment;

	GuiControl* entityDescription;
	GuiControl* entityNum;

	SDL_Rect menuBounds = {75,290-20,188,230};
	SDL_Rect subBounds;
	SDL_Rect optionsBounds;
	SDL_Rect detailsBounds;
	SDL_Rect actionsBounds;

	SDL_Texture* menus = nullptr;
	SDL_Texture* title = nullptr;
	SDL_Texture* entityImg = nullptr;		// 128*128
	SDL_Texture* capyinfo = nullptr;
	SDL_Texture* arrow = nullptr;
	

	SDL_Texture* textHP = nullptr;
	SDL_Texture* textMP = nullptr;
	
	int mainMenuOption;
	int subMenuOption;
	int actionOption;
	int selectorOption;
		
	Capybara* currentCapy = nullptr;
	Item* currentItem = nullptr;

	bool waitNextUpdate = false;
};


#endif // !__ITEM_MENU_H__
