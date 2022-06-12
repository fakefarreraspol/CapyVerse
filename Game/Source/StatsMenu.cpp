#include "StatsMenu.h"

#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "GuiManager.h"
#include "Textures.h"
#include "Input.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Inventory.h"
#include "EntityManager.h"
#include "Capybara.h"

#include "Log.h"
#include "SString.h"

StatsMenu::StatsMenu(bool startEnabled) :Module(startEnabled)
{
	name.Create("stats_menu");
}

StatsMenu::~StatsMenu()
{

}

bool StatsMenu::Awake(pugi::xml_node& node)
{
	LOG("Loading StatsMenu");
	bool ret = true;

	active = false;

	return ret;
}

bool StatsMenu::Start()
{
	app->guiManager->Enable();
	active = true;

	int offset = 50;
	subBounds = { menuBounds.x + menuBounds.w+ offset,150,700,520 };
	optionsBounds = { subBounds.x + subBounds.w + offset, menuBounds.y, 0,menuBounds.h };
	optionsBounds.w = 1280 - optionsBounds.x - offset;
	detailsBounds = subBounds;
	detailsBounds.w = 400;
	detailsBounds.x += subBounds.w-detailsBounds.w;

	entityDescription = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "item description",
		{ detailsBounds.x + 138, detailsBounds.y+10,detailsBounds.w - 138, detailsBounds.h },
		this, { 255,255,255,255 });
	
	SDL_Rect bounds = { detailsBounds.x, detailsBounds.y+128+20, 50,20 };
	entityNum = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "number", bounds, this, { 255,255,255,255 });

	entityDescription->state = GuiControlState::DISABLED;
		
	GuiButton* items = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "ITEMS", { 108, 300, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* capybaras = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "CAPYBARAS", { 108, 360, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* team = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "TEAM", { 108, 420, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* returnBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "RETURN", { 108, 480, 125, 20 }, this, { 255, 255, 255 });

	mainMenu.Add(items);
	mainMenu.Add(capybaras);
	mainMenu.Add(team);
	mainMenu.Add(returnBtn);

	//useBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 50, "USE", optionsBounds, this, { 255, 255, 255 });
	//equipBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 51, "EQUIP", optionsBounds, this, { 255, 255, 255 });
	////unequipBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 52, "UNEQUIP", { 108, 300, 125, 20 }, this, { 255, 255, 255 });



	bounds = { detailsBounds.x, detailsBounds.y + 200, 40,20 };	
	GuiControl* stats01 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "HP", bounds, this, { 255,255,255,255 }, 0, false);
	bounds.y += 30;
	GuiControl* stats02 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "MP", bounds, this, { 255,255,255,255 }, 0, false);
	bounds.y += 30;
	GuiControl* stats03 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "STR", bounds, this, { 255,255,255,255 }, 0, false);
	bounds.y += 30;
	GuiControl* stats04 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "SPD", bounds, this, { 255,255,255,255 }, 0, false);
	bounds.y += 30;
	GuiControl* stats05 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "ARM", bounds, this, { 255,255,255,255 }, 0, false);
	bounds.y += 30;
	GuiControl* stats06 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "INT", bounds, this, { 255,255,255,255 }, 0, false);

	stats.Add(stats01);
	stats.Add(stats02);
	stats.Add(stats03);
	stats.Add(stats04); 
	stats.Add(stats05);
	stats.Add(stats06);


	bounds = { detailsBounds.x+50, detailsBounds.y + 200, 40,20 };
	for (int i = 0; i < 6; i++)
	{
		bounds.y += 30 * i;
		GuiControl* c = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1+i, "  ", bounds, this, { 255,255,255,255 }, 0, false);
		c->state = GuiControlState::DISABLED;
		statsValue.Add(c);
	}

	for (int i = 0; i < 6; i++)
		stats.At(i)->data->state = GuiControlState::DISABLED;
	
	ActivateMenu();

	return true;
}


bool StatsMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool StatsMenu::Update(float dt)
{
	waitNextUpdate = false;

	iPoint cBounds = { app->render->camera.x, app->render->camera.y };
	SDL_Rect bounds;

	// print main menu rec
	bounds = { menuBounds.x - cBounds.x,menuBounds.y - cBounds.y,menuBounds.w, menuBounds.y };
	app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);


	if (currentMenu == &subMenu)
	{
		bounds = { subBounds.x - cBounds.x, subBounds.y - cBounds.y,subBounds.w, subBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
	}




	return true;
}

// Called before all Updates
bool StatsMenu::PostUpdate()
{
	return true;
}

// Called before quitting
bool StatsMenu::CleanUp()
{
	ClearMenu(&mainMenu);
	ClearMenu(&subMenu);
	ClearMenu(&actionsMenu);
	ClearMenu(&optionsMenu);
	return true;
}

bool StatsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	//---------------------------------- NEW UWU ------------------------------
	if (!waitNextUpdate)
	{
		waitNextUpdate = true;

		if (control->id == 1)		// main buttons
		{
			//hide actions and options or destroy other menus

			ClearMenu(&subMenu);
			ClearMenu(&actionsMenu);
			ClearMenu(&optionsMenu);


			if (control == mainMenu.At(0)->data)		// items
			{
				lastMain = 0;
				currentMenu = &subMenu;
				activeMenu = Menus::CAPY_INVENTORY;
				SDL_Rect bounds = subBounds;
				LoadItems(&subMenu, bounds, 2);
				entityNum->state = GuiControlState::NORMAL;
			}

			if (control == mainMenu.At(1)->data)	// capybaras + capy equipment and details
			{
				lastMain = 1;
				currentMenu = &subMenu;
				activeMenu = CAPY_INVENTORY;
				mainMenuOption = 1;
				control->state = GuiControlState::NORMAL;

				SDL_Rect bounds = subBounds;
				bounds.w -= detailsBounds.w;
				LoadCapys(&subMenu, bounds, 2);
			}

			// at 2 battle team

			if (control == mainMenu.At(3)->data)	// return
			{
				lastMain = 3;
				currentMenu = &mainMenu;
				activeMenu = MENU;

				HideMenus();

				active = false;
			}

		}

		if (control->id == 2)
		{
			ClearMenu(&actionsMenu);
			ClearMenu(&optionsMenu);

			int at = subMenu.Find(control);

			if (lastMain == 0)		// items
			{
				// load items details
				// show details and actions menu
			}

			if (lastMain == 1)		// capybaras
			{
				// load capy stats and equipment
			}

			if (lastMain == 2)		// battle team
			{
				
			}
		}

		if (control->id == 3)
		{
			ClearMenu(&optionsMenu);
		}

		if (control->id == 4)
		{
			// pos la accion final
		}

	}
	
	return true;
}

bool StatsMenu::ActivateMenu()
{
	active = true;

	mainMenu.At(0)->data->state = GuiControlState::NORMAL;
	mainMenu.At(1)->data->state = GuiControlState::NORMAL;
	mainMenu.At(2)->data->state = GuiControlState::NORMAL;
	mainMenu.At(3)->data->state = GuiControlState::NORMAL;

	return true;
}

bool StatsMenu::LoadCapys(List<GuiControl*> *menu, SDL_Rect bounds, int id)
{
	ClearMenu(menu);
	int offset = 10;
	SDL_Rect initialBounds = { bounds.x + 33, bounds.y + 10, bounds.w - 20,20 };


	List<Capybara*>* team = &app->scene->player->GetBattleTeam();

	int btns = bounds.h / 30;
	if (btns > team->Count())
		btns = team->Count();

	if (btns == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, "NO CAPYBARAS", initialBounds, this, { 255, 255, 255 });
		menu->Add(c);
	}
	else for (int i = 0; i < btns; i++)
	{
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);

		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, "CAPYBARA", bounds, this, { 255, 255, 255 });
		menu->Add(c);
	}


	return true;
}

bool StatsMenu::LoadItems(List<GuiControl*>* menu, SDL_Rect bounds, int id)
{
	ClearMenu(menu);
	SDL_Rect initialBounds = { subBounds.x + 33,subBounds.y + 10, subBounds.w - 60 - detailsBounds.w,20 };

	Inventory* inventory = app->entMan->inventory;

	int items = bounds.h / 30;
	if (items > inventory->slots.Count())
		items = inventory->slots.Count();

	int offset = 10;

	if (items == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "NO ITEMS", initialBounds, this, { 255, 255, 255 });
		menu->Add(c);
	}
	else for (int i = 0; i < items; i++)
	{
		currentItem = inventory->slots.At(i)->data->item;
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);
		GuiControl* c = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, currentItem->name.GetString(), bounds, this, { 255, 255, 255 });
		c->state = GuiControlState::NORMAL;
		menu->Add(c);


		// load stats    move to update details
		/*if (statsValue.Count() == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				bounds = stats.At(i)->data->bounds;
				bounds.x += 50;
				GuiControl* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1 + idStart, "  ", bounds, this, { 255,255,255,255 }, 0, false);
				statsValue.Add(c);
				c->state = GuiControlState::NORMAL;
			}
		}*/
		updateDetails = true;
	}


	return true;
}

bool StatsMenu::HideMenus()
{
	ListItem<GuiControl*>* c = mainMenu.start;

	while (c != nullptr)
	{ 
		c->data->state = GuiControlState::DISABLED;
		c = c->next;
	}

	// hide description buttons buttons
	

	return true;
}

bool StatsMenu::ClearMenu(List<GuiControl*>* menu)
{

	ListItem<GuiControl*>* c = menu->start;

	while (c!=nullptr)
	{
		GuiControl* del = c->data;
		c = c->next;
		app->guiManager->DestroyGuiControl(del);
	}
	menu->Clear();


	return true;
}
