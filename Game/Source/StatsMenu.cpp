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


	arrow = app->tex->Load("Assets/Menus/arrow.png");

	
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
	iPoint cBounds = { app->render->camera.x, app->render->camera.y };
	SDL_Rect bounds;

	GamePad& pad = app->input->pads[0];
	if (currentControls.Count() > 1)
	{
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down)
		{
			if (currentControl->next == nullptr)
			{
				currentControl->data->state = GuiControlState::NORMAL;
				currentControl = currentControls.start;
			}
			else
			{
				currentControl->data->state = GuiControlState::NORMAL;
				currentControl = currentControl->next;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up)
		{
			if (currentControl->prev == nullptr)
			{
				currentControl->data->state = GuiControlState::NORMAL;
				currentControl = currentControls.end;
			}
			else
			{
				currentControl->data->state = GuiControlState::NORMAL;
				currentControl = currentControl->prev;
			}
		}
	}
	

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left)
	{
		if (currentControls.start != menuBtns.start)
		{
			if (currentControls.start == itemsBtns.start)
			{
				ListItem<GuiControl*>* del = currentControls.start;
				while (del != nullptr)
				{
					GuiControl* p = del->data;
					app->guiManager->DestroyGuiControl(p);
					del = del->next;
				}
				entityDescription->state = GuiControlState::DISABLED;
				entityNum->state = GuiControlState::DISABLED;
				itemsBtns.Clear();
				capyBtns.Clear();
				teamBtns.Clear();
				currentControls = menuBtns;
				currentControl = currentControls.start;

				for (int i = 0; i < 6; i++)
				{
					stats.At(i)->data->state = GuiControlState::DISABLED;
					statsValue.At(i)->data->state = GuiControlState::DISABLED;
				}
			}
			if (currentControls.start == selectorBtns.start)
			{
				ListItem<GuiControl*>* del = currentControls.start;
				while (del != nullptr)
				{
					GuiControl* p = del->data;
					app->guiManager->DestroyGuiControl(p);
					del = del->next;
				}
				selectorBtns.Clear();
				currentControls = itemsBtns;
				currentControl = currentControls.start;

			}
				
		}
	}

	// stats menu

	bounds = { menuBounds.x - cBounds.x,menuBounds.y - cBounds.y,menuBounds.w,menuBounds.h };
	app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
	for (int i = 0; i < menuBtns.Count(); i++)
		menuBtns.At(i)->data->Draw(app->render);

	// inventory

	if (currentControls.start == itemsBtns.start)
	{
		app->render->DrawTexture(arrow, menuBtns.At(0)->data->bounds.x - 30, menuBtns.At(0)->data->bounds.y - 3, NULL, true);

		bounds = { subBounds.x - cBounds.x,subBounds.y - cBounds.y,subBounds.w,subBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
		bounds = { optionsBounds.x - cBounds.x,optionsBounds.y - cBounds.y,optionsBounds.w,optionsBounds.h };
		//app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);

		Inventory* inventory = app->entMan->inventory;
		Item* currentItem = nullptr;

		if (inventory->slots.Count() == 0)
		{
			if (itemsBtns.start != nullptr)
				itemsBtns.start->data->state = GuiControlState::NORMAL;
			entityDescription->state = GuiControlState::DISABLED;
		}

		// loading button info
		else for (int i = 0; i < itemsBtns.Count(); i++)
		{
			int at = i;
			itemsBtns.At(i)->data->SetText(inventory->slots.At(at)->data->item->name.GetString());
			if (at == currentControl->data->id - 10)
			{
				currentItem = inventory->slots.At(at)->data->item;
				SString num("x %i", inventory->slots.At(at)->data->cuantity);
				entityNum->SetText(num.GetString());
				entityDescription->SetText(currentItem->description.GetString());

				if (currentItem->category==ItemCategory::ARMOR|| currentItem->category == ItemCategory::NECKLACE|| currentItem->category == ItemCategory::WEAPON)
				{
					for (int i = 0; i < 6; i++)
					{
						stats.At(i)->data->state = GuiControlState::NORMAL;
						statsValue.At(i)->data->state = GuiControlState::NORMAL;
					}
						

					SString hp("%i", currentItem->stats.hp);
					SString mp("%i", currentItem->stats.mp);
					SString str("%i", currentItem->stats.strenght);
					SString spd("%i", currentItem->stats.speed);
					SString arm("%i", currentItem->stats.armor);
					SString inte("%i", currentItem->stats.intelligence);

					statsValue.At(0)->data->SetText(hp.GetString());
					statsValue.At(1)->data->SetText(mp.GetString());
					statsValue.At(2)->data->SetText(str.GetString());
					statsValue.At(3)->data->SetText(spd.GetString());
					statsValue.At(4)->data->SetText(arm.GetString());
					statsValue.At(5)->data->SetText(inte.GetString());
				}
				else
				{
					for (int i = 0; i < 6; i++)
					{
						stats.At(i)->data->state = GuiControlState::DISABLED;
						statsValue.At(i)->data->state = GuiControlState::DISABLED;
					}
				}
				
			}
			bounds = { detailsBounds.x + 10, detailsBounds.y - cBounds.y + 10, 128,128 };
			app->render->DrawRectangle(bounds, 255, 255, 255, 255, true, true);
			entityDescription->state = GuiControlState::NORMAL;
		}
		
		
	}

	if (currentControls.start == selectorBtns.start)
	{
		if (!currentControl)
			currentControl = selectorBtns.start;
		app->render->DrawTexture(arrow, menuBtns.At(mainMenuOption)->data->bounds.x - 30, menuBtns.At(mainMenuOption)->data->bounds.y - 3, NULL, true);

		app->render->DrawTexture(arrow, menuBtns.At(0)->data->bounds.x - 30, menuBtns.At(0)->data->bounds.y - 3, NULL, true);

		bounds = { subBounds.x - cBounds.x,subBounds.y - cBounds.y,subBounds.w,subBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
		bounds = { optionsBounds.x - cBounds.x,optionsBounds.y - cBounds.y,optionsBounds.w,optionsBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);

		if (app->scene->player->GetBattleTeam().Count() == 0)
		{
			if (selectorBtns.start != nullptr)
				selectorBtns.start->data->state = GuiControlState::NORMAL;
		}

		// loading button info
		else for (int i = 0; i < selectorBtns.Count(); i++)
		{
			int at = i;
			//selectorBtns.At(i)->data->SetText(app->scene->player->GetBattleTeam().At(at)->data->capyName.GetString());

			if (at == currentControl->data->id - 50)
			{
				Capybara* currentCapy = app->scene->player->GetBattleTeam().At(at)->data;
				
				

			}
			bounds = { detailsBounds.x + 10, detailsBounds.y - cBounds.y + 10, 128,128 };
			app->render->DrawRectangle(bounds, 255, 255, 255, 255, true, true);
			entityDescription->state = GuiControlState::NORMAL;
		}
	}

	/*if (activeMenu == Menus::ITEMS_ACTIONS)
	{
		app->render->DrawTexture(arrow, menuBtns.At(mainMenuOption)->data->bounds.x - 30, menuBtns.At(mainMenuOption)->data->bounds.y - 3, NULL, true);
		
	}*/

	

	// capybaras

	if (currentControls.start == capyBtns.start)
	{
		app->render->DrawTexture(arrow, menuBtns.At(1)->data->bounds.x - 30, menuBtns.At(1)->data->bounds.y - 3, NULL, true);

		bounds = { subBounds.x - cBounds.x,subBounds.y - cBounds.y,subBounds.w,subBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
		bounds = { optionsBounds.x - cBounds.x,optionsBounds.y - cBounds.y,optionsBounds.w,optionsBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);

		List<Capybara*> team = app->scene->player->GetTeam();
		Capybara* currentCapy = nullptr;

		if (team.Count() == 0)
		{
			if (capyBtns.start != nullptr)
				capyBtns.start->data->state = GuiControlState::NORMAL;
			entityDescription->state = GuiControlState::DISABLED;

		}
		else
		{
			for (int i = 0; i < capyBtns.Count(); i++)
			{
				int at = i;
				capyBtns.At(i)->data->SetText(team.At(at)->data->name.GetString());
				if (at == currentControl->data->id - 30)
				{
					currentCapy = team.At(at)->data;
					entityDescription->SetText(currentCapy->name.GetString());

				}
				//int at = (i + selectorOffset) % inventory->slots.Count();
			}
			bounds = { detailsBounds.x + 10, detailsBounds.y - cBounds.y + 10, 128,128 };
			app->render->DrawRectangle(bounds, 255, 255, 255, 255, true, true);
			entityDescription->state = GuiControlState::NORMAL;
		}
		
		
	}

	if(currentControl)
		app->render->DrawTexture(arrow, currentControl->data->bounds.x - 30, currentControl->data->bounds.y - 3, NULL, true);

	// stats menu





	if (currentControl)
		currentControl->data->state = GuiControlState::FOCUSED;


		

	return true;
}

// Called before all Updates
bool StatsMenu::PostUpdate()
{
	if (!active)
	{
		currentControl->data->state = GuiControlState::DISABLED;
		currentControl = nullptr;
	}
	return true;
}

// Called before quitting
bool StatsMenu::CleanUp()
{
	app->tex->UnLoad(arrow);
	menuBtns.Clear();
	itemsBtns.Clear();
	capyBtns.Clear();
	teamBtns.Clear();
	return true;
}

bool StatsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == 1) // items
	{
		activeMenu = ITEMS_INVENTORY;
		control->state = GuiControlState::NORMAL;
		mainMenuOption = 0;

		selectorOffset = 0;
		int offset = 10;
		SDL_Rect initialBounds = { subBounds.x + 33,subBounds.y + 10, subBounds.w - 60-detailsBounds.w,20 };

		Inventory* inventory = app->entMan->inventory;

		int items = 20;
		if (items > inventory->slots.Count())
			items = inventory->slots.Count();


		if (items == 0)
		{
			GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "NO ITEMS", initialBounds, this, { 255, 255, 255 });
			capyBtns.Add(c);
		}
		else for (int i = 0; i < items; i++)
		{
			SDL_Rect bounds = initialBounds;
			bounds.y += i * (offset + bounds.h);
			GuiControl* c = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 10, "ITEM", bounds, this, { 255, 255, 255 });
			itemsBtns.Add(c);

			if (statsValue.Count() == 0)
			{
				for (int i = 0; i < 6; i++)
				{
					bounds = stats.At(i)->data->bounds;
					bounds.x += 50;
					GuiControl* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "  ", bounds, this, { 255,255,255,255 }, 0, false);
					statsValue.Add(c);
					c->state = GuiControlState::NORMAL;
				}
			}
		}

		entityNum->state = GuiControlState::NORMAL;
		currentControls = itemsBtns;
		currentControl = currentControls.start;
		/*for (int i = 0; i < currentControls.Count(); i++)
			currentControls.At(i)->data->state = GuiControlState::NORMAL;*/
	}

	if (control->id == 2)	// capybaras
	{
		activeMenu = CAPY_INVENTORY;
		mainMenuOption = 1;
		control->state = GuiControlState::NORMAL;

		selectorOffset = 0;
		int offset = 10;
		SDL_Rect initialBounds = { subBounds.x + 33,subBounds.y + 10, subBounds.w - 60 - detailsBounds.w,20 };

		List<Capybara*>* team = &app->scene->player->GetTeam();

		int capys = 20;
		if (capys > team->Count())
			capys = team->Count();

		if (capys == 0)
		{
			GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 30, "NO CAPYBARAS", initialBounds, this, { 255, 255, 255 });
			capyBtns.Add(c);
		}
		else for (int i = 0; i < capys; i++)
		{
			SDL_Rect bounds = initialBounds;
			bounds.y += i * (offset + bounds.h);
			GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 30, "CAPYBARA", bounds, this, { 255, 255, 255 });
			capyBtns.Add(c);
		}

		currentControls = capyBtns;
		currentControl = currentControls.start;
	}

	if (control->id==3)
	{
		switch (control->id)
		{
		case 2:		currentControls = capyBtns;		break;
		case 3:		currentControls = teamBtns;		break;
		}

		currentControl = currentControls.start;
		for (int i = 0; i < currentControls.Count(); i++)
			currentControls.At(i)->data->state = GuiControlState::NORMAL;
	}

	if (control->id == 4)
	{
		mainMenuOption = 3;
		active = false;
		for (int i = 0; i < menuBtns.Count(); i++)
			currentControls.At(i)->data->state = GuiControlState::DISABLED;
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

			if (itemHolder->item->category == ItemCategory::CONSUMABLE)
			{
				LoadCapys(selectorBtns, optionsBounds);
				currentControls = selectorBtns;
				currentControl = selectorBtns.start;
				if (currentControl)
					currentControl->data->state = GuiControlState::FOCUSED;
			}
			/*if (itemHolder->item->category == ItemCategory::ARMOR
				|| itemHolder->item->category == ItemCategory::WEAPON
				|| itemHolder->item->category == ItemCategory::NECKLACE)
			{
				useBtn->state = GuiControlState::DISABLED;
				equipBtn->state = GuiControlState::FOCUSED;
			}*/
		}
	}


	return true;
}

bool StatsMenu::ActivateMenu()
{
	active = true;
	currentControls = menuBtns;
	currentControl = currentControls.start;

	for (int i = 0; i < currentControls.Count(); i++)
		currentControls.At(i)->data->state = GuiControlState::NORMAL;

	return true;
}

bool StatsMenu::LoadCapys(List<GuiControl*> menu, SDL_Rect bounds)
{
	int offset = 10;
	SDL_Rect initialBounds = { bounds.x + 10, bounds.y + 10, bounds.w - 20,20 };


	List<Capybara*>* team = &app->scene->player->GetBattleTeam();

	int btns = bounds.h / 30;
	if (btns > team->Count())
		btns = team->Count();

	if (btns == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 30, "NO CAPYBARAS", initialBounds, this, { 255, 255, 255 });
		capyBtns.Add(c);
	}
	else for (int i = 0; i < btns; i++)
	{
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);

		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 30, "CAPYBARA", bounds, this, { 255, 255, 255 });
		capyBtns.Add(c);
	}


	return true;
}