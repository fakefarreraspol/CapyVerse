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
{}

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
	GuiButton* capybaras = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "CAPYBARAS", { 108, 360, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* team = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "TEAM", { 108, 420, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* returnBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "RETURN", { 108, 480, 125, 20 }, this, { 255, 255, 255 });

	menuBtns.Add(items);
	menuBtns.Add(capybaras);
	menuBtns.Add(team);
	menuBtns.Add(returnBtn);

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
	menuBtns.Clear();
	itemsBtns.Clear();
	capyBtns.Clear();
	teamBtns.Clear();
	return true;
}

bool StatsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	if (!waitNextUpdate)
	{
		waitNextUpdate = true;
		if (control->id == 1) // items
		{
			activeMenu = ITEMS_INVENTORY;
			control->state = GuiControlState::NORMAL;
			mainMenuOption = 0;

			selectorOffset = 0;
			int offset = 10;

			SDL_Rect bounds = subBounds;

			LoadItems(&itemsBtns, bounds, 10);

			entityNum->state = GuiControlState::NORMAL;
			
			/*for (int i = 0; i < currentControls.Count(); i++)
				currentControls.At(i)->data->state = GuiControlState::NORMAL;*/
		}

		if (control->id == 2)	// capybaras
		{
			activeMenu = CAPY_INVENTORY;
			mainMenuOption = 1;
			control->state = GuiControlState::NORMAL;

			SDL_Rect bounds = subBounds;
			bounds.w -= detailsBounds.w;
			LoadCapys(&capyBtns, bounds, 30);
		}

		if (control->id == 4)
		{
			mainMenuOption = 3;
			active = false;
		}

		if (control->id >= 10 && control->id <= 29) // items inventory
		{
			activeMenu = ITEMS_ACTIONS;
			control->state = GuiControlState::NORMAL;
			int at = control->id - 10;
			subMenuOption = at;

			ItemHolder* itemHolder = app->entMan->inventory->slots.At(at)->data;
			if (itemHolder->cuantity > 0)
			{
				//currentControls = actionsBtns;

				if (itemHolder->item->category != ItemCategory::OBJECT
					|| itemHolder->item->category != ItemCategory::NONE)
				{
					LoadCapys(&selectorBtns, optionsBounds, 50);
				}
			}
		}

		if (control->id >= 50 && control->id <= 69)
		{
			currentCapy = app->scene->player->GetBattleTeam().At(control->id - 50)->data;

			if (currentItem->category==ItemCategory::CONSUMABLE)
				app->entMan->inventory->UseItem(currentItem, currentCapy);
			else
				app->entMan->inventory->EquipItem(currentItem, currentCapy);

			LoadItems(&itemsBtns, subBounds, 10);

			entityDescription->state = GuiControlState::DISABLED;
			entityNum->state = GuiControlState::DISABLED;
		}
	}
	
	return true;
}

bool StatsMenu::ActivateMenu()
{
	active = true;


	return true;
}

bool StatsMenu::LoadCapys(List<GuiControl*> *menu, SDL_Rect bounds, int idStart)
{
	if (menu->Count() > 0)
	{
		ListItem<GuiControl*>* c = menu->start;
		while (c)
		{
			GuiControl* del = c->data;
			c = c->next;
			app->guiManager->DestroyGuiControl(del);
		}
		menu->Clear();
	}
	int offset = 10;
	SDL_Rect initialBounds = { bounds.x + 10, bounds.y + 10, bounds.w - 20,20 };


	List<Capybara*>* team = &app->scene->player->GetBattleTeam();

	int btns = bounds.h / 30;
	if (btns > team->Count())
		btns = team->Count();

	if (btns == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, idStart, "NO CAPYBARAS", initialBounds, this, { 255, 255, 255 });
		menu->Add(c);
	}
	else for (int i = 0; i < btns; i++)
	{
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);

		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + idStart, "CAPYBARA", bounds, this, { 255, 255, 255 });
		menu->Add(c);
	}


	return true;
}

bool StatsMenu::LoadItems(List<GuiControl*>* menu, SDL_Rect bounds, int idStart)
{
	if (menu->Count() >= 0)
	{
		ListItem<GuiControl*>* c = menu->start;
		while (c)
		{
			GuiControl* del = c->data;
			c = c->next;
			app->guiManager->DestroyGuiControl(del);
		}
		menu->Clear();
	}
	SDL_Rect initialBounds = { subBounds.x + 33,subBounds.y + 10, subBounds.w - 60 - detailsBounds.w,20 };

	Inventory* inventory = app->entMan->inventory;

	int items = bounds.h / 30;
	if (items > inventory->slots.Count())
		items = inventory->slots.Count();

	int offset = 10;

	if (items == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "NO ITEMS", initialBounds, this, { 255, 255, 255 });
		capyBtns.Add(c);
	}
	else for (int i = 0; i < items; i++)
	{
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);
		GuiControl* c = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + idStart, "ITEM", bounds, this, { 255, 255, 255 });
		c->state = GuiControlState::NORMAL;
		itemsBtns.Add(c);

		if (statsValue.Count() == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				bounds = stats.At(i)->data->bounds;
				bounds.x += 50;
				GuiControl* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1 + idStart, "  ", bounds, this, { 255,255,255,255 }, 0, false);
				statsValue.Add(c);
				c->state = GuiControlState::NORMAL;
			}


		}
	}
	return true;
}