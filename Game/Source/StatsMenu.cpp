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

#include "Log.h"

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

	GuiButton* items = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "ITEMS", { 108, 300, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* capybaras = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "CAPYBARAS", { 108, 360, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* team = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "TEAM", { 108, 420, 125, 20 }, this, { 255, 255, 255 });
	GuiButton* returnBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "RETURN", { 108, 480, 125, 20 }, this, { 255, 255, 255 });

	menuBtns.Add(items);
	menuBtns.Add(capybaras);
	menuBtns.Add(team);
	menuBtns.Add(returnBtn);

	
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

	// stats menu

	bounds = { menuBounds.x - cBounds.x,menuBounds.y - cBounds.y,menuBounds.w,menuBounds.h };
	app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);
	for (int i = 0; i < menuBtns.Count(); i++)
		menuBtns.At(i)->data->Draw(app->render);


	if (currentControls.start == itemsBtns.start)
	{
		app->render->DrawTexture(arrow, menuBtns.At(0)->data->bounds.x - 30, menuBtns.At(0)->data->bounds.y - 3, NULL, true);

		bounds = { itemsBounds.x - cBounds.x,itemsBounds.y - cBounds.y,itemsBounds.w,itemsBounds.h };
		app->render->DrawRectangle(bounds, 0, 0, 0, 255, true, true);

		Inventory* inventory = app->scene->player->inventory;

		for (int i = 0; i < currentControls.Count(); i++)
		{
			int at = (i + selectorOffset) % inventory->slots.Count();
			currentControls.At(i)->data->text.Create(inventory->slots.At(at)->data->item->name.GetString());
		}


	}

	app->render->DrawTexture(arrow, currentControl->data->bounds.x - 30, currentControl->data->bounds.y - 3, NULL, true);

	// stats menu






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
		control->state = GuiControlState::NORMAL;
		
		selectorOffset = 0;
		int offset = 10;
		SDL_Rect initialBounds = { itemsBounds.x + 33,itemsBounds.y + 10, itemsBounds.w - 60,20 };

		Inventory* inventory = app->scene->player->inventory;

		int items = 10;
		if (items > inventory->slots.Count())
			items = inventory->slots.Count();

		for (int i = 0; i < items; i++)
		{
			SDL_Rect bounds = { initialBounds.x, initialBounds.y + 20+ i*offset,initialBounds.w, initialBounds.h };
			GuiButton* c = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 10, "", bounds, this, { 255, 255, 255 });
			itemsBtns.Add(c);
		}

		currentControls = itemsBtns;
		currentControl = currentControls.start;
		for (int i = 0; i < currentControls.Count(); i++)
			currentControls.At(i)->data->state = GuiControlState::NORMAL;
	}


	if (control->id >= 1 && control->id <= 3)
	{
		switch (control->id)
		{
		case 1:		currentControls = itemsBtns;	break;
		case 2:		currentControls = capyBtns;		break;
		case 3:		currentControls = teamBtns;		break;
		}

		currentControl = currentControls.start;
		for (int i = 0; i < currentControls.Count(); i++)
			currentControls.At(i)->data->state = GuiControlState::NORMAL;
	}

	if (control->id == 4)
	{
		active = false;
		for (int i = 0; i < currentControls.Count(); i++)
			currentControls.At(i)->data->state = GuiControlState::DISABLED;
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