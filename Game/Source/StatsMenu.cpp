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
#include "Fonts.h"

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
	optionsBounds = { subBounds.x + subBounds.w + offset-20, menuBounds.y, 0,menuBounds.h };
	optionsBounds.w = 1280 - optionsBounds.x - offset;
	detailsBounds = subBounds;
	detailsBounds.w = 400;
	detailsBounds.x += subBounds.w-detailsBounds.w;

	entityDescription = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "item description",
		{ detailsBounds.x + 138, detailsBounds.y+10,detailsBounds.w - 138, detailsBounds.h },
		this, { 255,255,255,255 });
	
	SDL_Rect bounds = { detailsBounds.x, detailsBounds.y+128+20, 50,20 };
	entityNum = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "number", bounds, this, { 255,255,255,255 });
	entityNum->state = GuiControlState::DISABLED;

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
	
	// textures
	capyinfo = app->tex->Load("Assets/Menus/menus.png");
	SDL_Rect rec = { 0,0,50,10 };
	textHP = app->fonts->LoadRenderedText(rec, 1, "HP", { 255,255,255,255 });
	textMP = app->fonts->LoadRenderedText(rec, 1, "MP", { 255,255,255,255 });
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
	waitNextUpdate = false;

	iPoint cBounds = { app->render->camera.x, app->render->camera.y };
	SDL_Rect bounds;

	// print main menu rec
	bounds = { menuBounds.x - cBounds.x,menuBounds.y - cBounds.y,menuBounds.w, menuBounds.y };
	app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);


	if (currentMenu == &subMenu || currentMenu == &actionsMenu|| currentMenu==&optionsMenu)
	{
		bounds = { subBounds.x - cBounds.x, subBounds.y - cBounds.y,subBounds.w, subBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
		app->render->DrawTexture(arrow, mainMenu.At(lastMain)->data->bounds.x - 30, mainMenu.At(lastMain)->data->bounds.y - 3, NULL, true);

		if (lastMain == 2)		// draw battle team
		{
			SDL_Rect info{ 0, 255, 270, 122 };

			SDL_Rect bounds = info;
			bounds.x = subBounds.x - cBounds.x + 10;
			bounds.y = subBounds.y - cBounds.y + 10;

			for (int i = 0; i < 3; i++)
			{

				SDL_Rect rec1 = { bounds.x + 10, bounds.y + 70, info.w - 50, 10 };
				SDL_Rect rec2 = { rec1.x, rec1.y + 25, rec1.w, 10 };
				app->render->DrawTexture(capyinfo, bounds.x, bounds.y, &info);


				List<Capybara*>* team = &app->scene->player->GetBattleTeam();
				if (team->At(i))
				{
					

					app->render->DrawRectangle(rec1, 255, 255, 255, 50, true, true);
					app->render->DrawRectangle(rec2, 255, 255, 255, 50, true, true);
					app->render->DrawTexture(textHP, rec1.x + rec1.w+3, rec1.y-3);
					app->render->DrawTexture(textMP, rec1.x + rec1.w+3, rec2.y-3);

					float hp= rec1.w*team->At(i)->data->GetHealth() / team->At(i)->data->GetMaxHealth();
					float mp= rec2.w*team->At(i)->data->GetMana() / team->At(i)->data->GetMaxMana();
					rec1.w = (int)hp;
					rec2.w = (int)mp;

					app->render->DrawRectangle(rec1, 255, 255, 255, 150, true, true);
					app->render->DrawRectangle(rec2, 255, 255, 255, 150, true, true);

				}

				bounds.y += bounds.h + 20;

			}
		}

		if (currentMenu == &actionsMenu || currentMenu == &optionsMenu)
		{
			app->render->DrawTexture(arrow, subMenu.At(lastSub)->data->bounds.x - 30, subMenu.At(lastSub)->data->bounds.y - 3, NULL, true);

			if (currentMenu == &optionsMenu)
			{
				bounds = { optionsBounds.x - cBounds.x + 10, optionsBounds.y - cBounds.y,optionsBounds.w + 5, optionsBounds.h };
				app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
				app->render->DrawTexture(arrow, actionsMenu.At(lastActions)->data->bounds.x - 30, actionsMenu.At(lastActions)->data->bounds.y - 3, NULL, true);
			}
		}

		
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
	ClearMenu(&stats);
	ClearMenu(&statsValue);
	ClearMenu(&equipment);


	app->guiManager->DestroyGuiControl(entityDescription);
	app->guiManager->DestroyGuiControl(entityNum);

	app->tex->UnLoad(menus);
	app->tex->UnLoad(title);
	app->tex->UnLoad(entityImg);
	app->tex->UnLoad(capyinfo);
	app->tex->UnLoad(arrow);
	app->tex->UnLoad(textHP);
	app->tex->UnLoad(textMP);


	return true;
}

bool StatsMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	if (!waitNextUpdate)
	{
		waitNextUpdate = true;

		if (control->id==0)		//equipment
		{

		}


		if (control->id == 1)		// main buttons
		{
			//hide actions and options or destroy other menus
			currentMenu = &subMenu;

			ClearMenu(&subMenu);
			ClearMenu(&actionsMenu);
			ClearMenu(&optionsMenu);
			ClearMenu(&equipment);

			entityDescription->state = GuiControlState::DISABLED;
			entityNum->state = GuiControlState::DISABLED;

			for (int i = 0; i < 6; i++)
			{
				stats.At(i)->data->state = GuiControlState::DISABLED;
				statsValue.At(i)->data->state = GuiControlState::DISABLED;
			}

			if (control == mainMenu.At(0)->data)		// items
			{
				lastMain = 0;
				SDL_Rect bounds = subBounds;
				LoadItems(&subMenu, bounds, 2);
			}

			if (control == mainMenu.At(1)->data)	// capybaras + capy equipment and details
			{
				lastMain = 1;
				mainMenuOption = 1;
				control->state = GuiControlState::NORMAL;

				SDL_Rect bounds = subBounds;
				bounds.w -= detailsBounds.w;
				LoadCapys(&subMenu, bounds, 2);
			}

			if (control == mainMenu.At(2)->data)		// battle team
			{
				lastMain = 2;

				SDL_Rect info{ 0, 255, 270, 122 };
				SDL_Rect bounds = info;
				bounds.x = subBounds.x;
				bounds.y = subBounds.y;

				LoadTeam(&subMenu, bounds, 2);
				List<Capybara*>* team = &app->scene->player->GetBattleTeam();

				for (int i = 0; i < subMenu.Count(); i++)
				{
					if (team->At(i))
					{
						subMenu.At(i)->data->bounds.y = bounds.y + 50;
						subMenu.At(i)->data->bounds.w -= 20;

					}
					bounds.y += bounds.h + 20;

				}
			}

			if (control == mainMenu.At(3)->data)	// return
			{
				lastMain = 3;

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
			currentMenu = &actionsMenu;

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
				if (control->text.GetString() != "NO CAPYBARAS")
				{
					List<Capybara*>* team = &app->scene->player->GetTeam();
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

					SDL_Rect bounds = stats.end->data->bounds;
					bounds.w = 60;
					SString text;

					if (currentCapy->armorItem) text.Create(currentCapy->armorItem->name.GetString());
					else text.Create("no armor");
					bounds.y += 40;
					GuiControl* armor = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

					if (currentCapy->necklaceItem) text.Create(currentCapy->necklaceItem->name.GetString());
					else text.Create("no necklace");
					bounds.y += 30;
					GuiControl* necklace = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

					if (currentCapy->weaponItem) text.Create(currentCapy->weaponItem->name.GetString());
					else text.Create("no weapon");
					bounds.y += 30;
					GuiControl* weapon = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

					armor->state = GuiControlState::NORMAL;
					necklace->state = GuiControlState::NORMAL;
					weapon->state = GuiControlState::NORMAL;
					equipment.Add(armor);
					equipment.Add(necklace);
					equipment.Add(weapon);

					bounds = actionsBounds;
					bounds.h = 20;
					GuiButton* action1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "EQUIP", bounds, this, { 255, 255, 255 });
					bounds.y += 30;

					action1->state = GuiControlState::NORMAL;

					actionsMenu.Add(action1);
				}

				
			}

			if (lastMain == 2)		// battle team
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

				SDL_Rect bounds = stats.end->data->bounds;
				bounds.w = 60;
				SString text;

				if (currentCapy->armorItem) text.Create(currentCapy->armorItem->name.GetString());
				else text.Create("no armor");
				bounds.y += 40;
				GuiControl* armor = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

				if (currentCapy->necklaceItem) text.Create(currentCapy->necklaceItem->name.GetString());
				else text.Create("no necklace");
				bounds.y += 30;
				GuiControl* necklace = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

				if (currentCapy->weaponItem) text.Create(currentCapy->weaponItem->name.GetString());
				else text.Create("no weapon");
				bounds.y += 30;
				GuiControl* weapon = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

				armor->state = GuiControlState::NORMAL;
				necklace->state = GuiControlState::NORMAL;
				weapon->state = GuiControlState::NORMAL;
				equipment.Add(armor);
				equipment.Add(necklace);
				equipment.Add(weapon);

				bounds = actionsBounds;
				bounds.h = 20;
				GuiButton* action1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "CHANGE", bounds, this, { 255, 255, 255 });
				bounds.y += 30;
				GuiButton* action2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "USE ITEM", bounds, this, { 255, 255, 255 });
				bounds.y += 30;

				action1->state = GuiControlState::NORMAL;
				action2->state = GuiControlState::NORMAL;

				actionsMenu.Add(action1);
				actionsMenu.Add(action2);
			}
		}

		if (control->id == 3)
		{
			ClearMenu(&optionsMenu);
			int at = actionsMenu.Find(control);
			lastActions = at;
			currentMenu = &optionsMenu;
			
			if (lastMain == 0)// items
			{
				if (control == actionsMenu.At(0)->data)		// use
				{
					currentMenu = &optionsMenu;
					LoadTeam(&optionsMenu,optionsBounds,4);
				}
				if (control == actionsMenu.At(1)->data)		// throw
				{
					ItemHolder* holder = app->entMan->inventory->slots.At(lastSub)->data;
					int cuantity = holder->cuantity - 1;
					app->entMan->inventory->DelItem(holder->item);
					app->entMan->inventory->DeleteEmpty();
					LoadItems(&subMenu, subBounds, 2);

					if (cuantity > 0)
					{
						SString num("x %i", holder->cuantity);
						entityNum->SetText(num.GetString());
						currentMenu = &subMenu;
					}
					else
					{
						actionsMenu.At(0)->data->state = GuiControlState::DISABLED;
						actionsMenu.At(1)->data->state = GuiControlState::DISABLED;
						
						entityDescription->state= GuiControlState::DISABLED;
						entityNum->state= GuiControlState::DISABLED;

						for (int i = 0; i < 6; i++)
						{
							stats.At(i)->data->state = GuiControlState::DISABLED;
							statsValue.At(i)->data->state= GuiControlState::DISABLED;
						}

						currentMenu = &subMenu;
					}
					
				}
			}
			if (lastMain == 1)// capys
			{
				if (control == actionsMenu.At(0)->data)
				{
					currentMenu = &optionsMenu;
					LoadTeam(&optionsMenu, optionsBounds, 4);
				}
			}
			if (lastMain == 2)// team
			{
				if (control == actionsMenu.At(0)->data)			// change
				{
					currentMenu = &optionsMenu;
					LoadCapys(&optionsMenu, optionsBounds, 4);
				}
				if (control == actionsMenu.At(1)->data)			// use item
				{
					currentMenu = &optionsMenu;
					LoadItems(&optionsMenu, optionsBounds, 4);
				}
			}
		}

		if (control->id == 4)
		{
			int at = optionsMenu.Find(control);
			lastOptions = at;

			if (lastMain == 0)	// items
			{
				if (lastActions == 0)
				{

					ItemHolder* holder = app->entMan->inventory->slots.At(lastSub)->data;
					int cuantity = holder->cuantity - 1;
					currentCapy = app->scene->player->GetBattleTeam().At(at)->data;

					if (currentItem->category == ItemCategory::CONSUMABLE)
						app->entMan->inventory->UseItem(currentItem, currentCapy);
					else
						app->entMan->inventory->EquipItem(currentItem, currentCapy);

					app->entMan->inventory->DeleteEmpty();
					LoadItems(&subMenu, subBounds, 2);

					if (cuantity > 0)
					{
						SString num("x %i", holder->cuantity);
						entityNum->SetText(num.GetString());
					}
					else
					{
						actionsMenu.At(0)->data->state = GuiControlState::DISABLED;
						actionsMenu.At(1)->data->state = GuiControlState::DISABLED;

						entityDescription->state = GuiControlState::DISABLED;
						entityNum->state = GuiControlState::DISABLED;

						for (int i = 0; i < 6; i++)
						{
							stats.At(i)->data->state = GuiControlState::DISABLED;
							statsValue.At(i)->data->state = GuiControlState::DISABLED;
						}

						currentMenu = &subMenu;
					}
				}
			}

			if (lastMain == 1)	// capys
			{
				if (lastActions == 0)			// equip
				{
					Capybara* optionCapy = app->scene->player->GetBattleTeam().At(at)->data;
					app->scene->player->ChangeCapybaras(currentCapy, optionCapy);

				}
			}

			if (lastMain == 2)	// battle team
			{
				if (lastActions == 0)			// change
				{
					Capybara* optionCapy = app->scene->player->GetTeam().At(at)->data;
					
					app->scene->player->ChangeCapybaras(optionCapy, currentCapy);
				}
				if(lastActions == 1)			// use item
				{
					ItemHolder* holder = app->entMan->inventory->slots.At(at)->data;
					int cuantity = holder->cuantity - 1;
					currentItem = holder->item;

					if (currentItem->category == ItemCategory::CONSUMABLE)
						app->entMan->inventory->UseItem(currentItem, currentCapy);
					else
						app->entMan->inventory->EquipItem(currentItem, currentCapy);

					app->entMan->inventory->DeleteEmpty();

					for (int i = 0; i < optionsMenu.Count(); i++)
						optionsMenu.At(i)->data->state = GuiControlState::DISABLED;
					currentMenu = &actionsMenu;

					// update stats

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

					ClearMenu(&equipment);

					SDL_Rect bounds = stats.end->data->bounds;
					bounds.w = 60;
					SString text;

					if (currentCapy->armorItem) text.Create(currentCapy->armorItem->name.GetString());
					else text.Create("no armor");
					bounds.y += 40;
					GuiControl* armor = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

					if (currentCapy->necklaceItem) text.Create(currentCapy->necklaceItem->name.GetString());
					else text.Create("no necklace");
					bounds.y += 30;
					GuiControl* necklace = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

					if (currentCapy->weaponItem) text.Create(currentCapy->weaponItem->name.GetString());
					else text.Create("no weapon");
					bounds.y += 30;
					GuiControl* weapon = app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, text.GetString(), bounds, this, { 255,255,255,255 }, 0, false);

					armor->state = GuiControlState::NORMAL;
					necklace->state = GuiControlState::NORMAL;
					weapon->state = GuiControlState::NORMAL;
					equipment.Add(armor);
					equipment.Add(necklace);
					equipment.Add(weapon);
				}
			}
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

bool StatsMenu::LoadTeam(List<GuiControl*> *menu, SDL_Rect bounds, int id)
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
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, -1, "NO CAPYBARAS", initialBounds, this, { 255, 255, 255 });
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

bool StatsMenu::LoadCapys(List<GuiControl*>* menu, SDL_Rect bounds, int id)
{
	ClearMenu(menu);
	int offset = 10;
	SDL_Rect initialBounds = { bounds.x + 33, bounds.y + 10, bounds.w - 20,20 };


	List<Capybara*>* battleTeam = &app->scene->player->GetTeam();

	int btns = bounds.h / 30;
	if (btns > battleTeam->Count())
		btns = battleTeam->Count();

	if (btns == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, -1, "NO CAPYBARAS", initialBounds, this, { 255, 255, 255 });
		menu->Add(c);
	}
	else for (int i = 0; i < btns; i++)
	{
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);

		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, battleTeam->At(i)->data->name.GetString(), bounds, this, { 255, 255, 255 });
		menu->Add(c);
	}


	return true;
}

bool StatsMenu::LoadItems(List<GuiControl*>* menu, SDL_Rect bounds, int id)
{
	ClearMenu(menu);
	SDL_Rect initialBounds;
	if (id == 2)
		initialBounds = { bounds.x + 33,bounds.y + 10, bounds.w - 60 - detailsBounds.w,20 };
	else
		initialBounds = { bounds.x + 33,bounds.y + 10, bounds.w - 40,20 };

	Inventory* inventory = app->entMan->inventory;

	int items = bounds.h / 30;
	if (items > inventory->slots.Count())
		items = inventory->slots.Count();

	int offset = 10;

	if (items == 0)
	{
		GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, -1, "NO ITEMS", initialBounds, this, { 255, 255, 255 });
		menu->Add(c);
	}
	else for (int i = 0; i < items; i++)
	{
		SDL_Rect bounds = initialBounds;
		bounds.y += i * (offset + bounds.h);
		GuiControl* c = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, inventory->slots.At(i)->data->item->name.GetString(), bounds, this, { 255, 255, 255 });
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
