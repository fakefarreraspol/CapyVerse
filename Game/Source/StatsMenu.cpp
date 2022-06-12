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


	actionsBounds = { stats01->bounds.x + 200, stats01->bounds.y,detailsBounds.w,detailsBounds.h };
	actionsBounds.w -= actionsBounds.x - detailsBounds.x+10;
	actionsBounds.h -= actionsBounds.y - detailsBounds.y;

	bounds = { detailsBounds.x+50, detailsBounds.y + 200, 40,20 };
	for (int i = 0; i < 6; i++)
	{
		GuiControl* c = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1+i, "  ", bounds, this, { 255,255,255,255 }, 0, false);
		c->state = GuiControlState::DISABLED;
		statsValue.Add(c);
		bounds.y += 30;
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
			ClearMenu(&equipment);

			for (int i = 0; i < 6; i++)
			{
				stats.At(i)->data->state = GuiControlState::DISABLED;
				statsValue.At(i)->data->state = GuiControlState::DISABLED;
			}

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
			ClearMenu(&equipment);

			int at = subMenu.Find(control);
			lastSub = at;

			if (lastMain == 0)		// items
			{
				ItemHolder* slot = app->entMan->inventory->slots.At(at)->data;
				currentItem = slot->item;

				for (int i = 0; i < 6; i++)
				{
					stats.At(i)->data->state = GuiControlState::NORMAL;
					statsValue.At(i)->data->state = GuiControlState::NORMAL;
				}
				
				SString num0("%i", currentItem->stats.hp);
				statsValue.At(0)->data->SetText(num0.GetString());
				SString num1("%i", currentItem->stats.mp);
				statsValue.At(1)->data->SetText(num1.GetString());
				SString num2("%i", currentItem->stats.strenght);
				statsValue.At(2)->data->SetText(num2.GetString());
				SString num3("%i", currentItem->stats.speed);
				statsValue.At(3)->data->SetText(num3.GetString());
				SString num4("%i", currentItem->stats.armor);
				statsValue.At(4)->data->SetText(num4.GetString());
				SString num5("%i", currentItem->stats.intelligence);
				statsValue.At(5)->data->SetText(num5.GetString());

				entityDescription->state = GuiControlState::NORMAL;
				entityNum->state = GuiControlState::NORMAL;

				SString num("x %i", slot->cuantity);
				entityNum->SetText(num.GetString());
				entityDescription->SetText(slot->item->description.GetString());

				// show details and actions menu
				//SDL_Rect bounds = stats.start->data->bounds;

				if (currentItem->category != ItemCategory::OBJECT)
				{
					SDL_Rect bounds = actionsBounds;
					bounds.h = 20;
					GuiButton* action1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "USE / EQUP", bounds, this, { 255, 255, 255 });
					bounds.y += 30;
					GuiButton* action2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "THROW", bounds, this, { 255, 255, 255 });

					action1->state = GuiControlState::NORMAL;
					action2->state = GuiControlState::NORMAL;

					actionsMenu.Add(action1);
					actionsMenu.Add(action2);
				}
			}

			if (lastMain == 1)		// capybaras
			{
				List<Capybara*>* team = &app->scene->player->GetBattleTeam();
				currentCapy = team->At(at)->data;


				// stats description
				for (int i = 0; i < 6; i++)
				{
					stats.At(i)->data->state = GuiControlState::NORMAL;
					statsValue.At(i)->data->state = GuiControlState::NORMAL;
				}
				SString num0("%i", currentCapy->GetStats().hp);
				statsValue.At(0)->data->SetText(num0.GetString());
				SString num1("%i", currentCapy->GetStats().mp);
				statsValue.At(1)->data->SetText(num1.GetString());
				SString num2("%i", currentCapy->GetStats().strenght);
				statsValue.At(2)->data->SetText(num2.GetString());
				SString num3("%i", currentCapy->GetStats().speed);
				statsValue.At(3)->data->SetText(num3.GetString());
				SString num4("%i", currentCapy->GetStats().armor);
				statsValue.At(4)->data->SetText(num4.GetString());
				SString num5("%i", currentCapy->GetStats().intelligence);
				statsValue.At(5)->data->SetText(num5.GetString());

				// description and level
				entityDescription->state = GuiControlState::NORMAL;
				entityNum->state = GuiControlState::NORMAL;
				SString num("LVL %i", currentCapy->GetLVL());
				entityNum->SetText(num.GetString());
				entityDescription->SetText("...");

				//GuiControl* armor= GuiText::

				SDL_Rect bounds = actionsBounds;
				bounds.h = 20;
				GuiButton* action1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "EQUIP", bounds, this, { 255, 255, 255 });
				bounds.y += 30;

				action1->state = GuiControlState::NORMAL;

				actionsMenu.Add(action1);
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

		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, team->At(i)->data->name.GetString(), bounds, this, {255, 255, 255});
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
