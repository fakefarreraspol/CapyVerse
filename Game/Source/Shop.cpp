#include "Shop.h"
#include "App.h"
#include "Scene.h"
#include "EntityManager.h"
#include "GuiManager.h"
#include "Player.h"

Shop::Shop(bool startEnabled) : Module(startEnabled)
{
}

Shop::~Shop()
{
}

bool Shop::Awake(pugi::xml_node&)
{
	shopInventory = new Inventory();

	return true;
}

bool Shop::Start()
{

	Item* item01 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::HP_POTION);
	Item* item02 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::MP_POTION);
	Item* item03 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::REVIVE);
	Item* item04 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::FREERUNERS_ARMOR);
	Item* item05 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::BOW_SPELLDRINKER);
	Item* item06 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::ARMOR_VULNERABILITY);


	shopInventory->AddItem(item01, 999);
	shopInventory->AddItem(item02, 999);
	shopInventory->AddItem(item03, 999);
	shopInventory->AddItem(item04, 999);
	shopInventory->AddItem(item05, 999);
	shopInventory->AddItem(item06, 999);

	int i = 0;
	for (ListItem<ItemHolder*>* item = shopInventory->slots.start; item != nullptr; item = item->next)
	{
		const char* itemName = item->data->item->name.GetString();
		itemsBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 100 + i, itemName, { 500, 200 + i * 20, 300, 20 }, this));
		i++;
	}

	buyBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 69, "Buy", { 450, 150, 100, 20 }, this);
	sellBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 70, "Sell", { 650, 150, 100, 20 }, this);
	returnBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 71, "Return", { 450, 500, 100, 20 }, this);
	if (app->scene->player)
	{
		playerMoney = app->scene->player->money;
	}
	SString money("Capycoins: %i ", playerMoney);
	playerMoneyTxt = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, money.GetString(), { 750, 100, 100, 50 }, this);
	
	UnShow();

	return true;
}

bool Shop::PreUpdate()
{
	return true;
}

bool Shop::Update(float dt)
{
	playerMoney = app->scene->player->money;
	SString money("Capycoins: %i ", playerMoney);
	if (strcmp(playerMoneyTxt->GetText(), money.GetString()))
	{
		playerMoneyTxt->SetText(money.GetString());
	}

	return true;
}

void Shop::Show()
{
	playerMoneyTxt->state = GuiControlState::NORMAL;
	buyBtn->state = GuiControlState::NORMAL;
	sellBtn->state = GuiControlState::NORMAL;
	returnBtn->state = GuiControlState::NORMAL;

	for (int i = 0; i < itemsBtns.Count(); i++)
	{
		itemsBtns.At(i)->data->state = GuiControlState::NORMAL;
	}
}

void Shop::UnShow()
{
	playerMoneyTxt->state = GuiControlState::DISABLED;
	buyBtn->state = GuiControlState::DISABLED;
	sellBtn->state = GuiControlState::DISABLED;
	returnBtn->state = GuiControlState::DISABLED;

	for (int i = 0; i < itemsBtns.Count(); i++)
	{
		itemsBtns.At(i)->data->state = GuiControlState::DISABLED;
	}
}

bool Shop::PostUpdate()
{
	return true;
}

bool Shop::CleanUp()
{
	return true;
}

bool Shop::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id >= 100 && control->id <= 100 + itemsBtns.Count())
	{
		int id = control->id - 100;
		Item* item = shopInventory->slots.At(id)->data->item;
		if (buy)
		{
			if (playerMoney >= item->price)
			{
				printf("Item: %s, bought\n", item->name.GetString());
				app->entMan->inventory->AddItem(item, 1);
				shopInventory->DelItem(item, 1);
				app->scene->player->money -= item->price;
			}
			else
			{
				printf("Item: %s, is too expensive!\n", item->name.GetString());
			}
		}
		else
		{
			app->entMan->inventory->DelItem(item, 1);
			app->scene->player->money += item->price;
		}
	}
	if (control->id == 69) 
	{
		for (ListItem<GuiButton*>* btn = itemsBtns.start; btn != nullptr; btn = btn->next)
		{
			app->guiManager->DestroyGuiControl(btn->data);
		}
		itemsBtns.Clear();
		int i = 0;
		for (ListItem<ItemHolder*>* item = shopInventory->slots.start; item != nullptr; item = item->next)
		{
			const char* itemName = item->data->item->name.GetString();
			itemsBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 100 + i, itemName, { 500, 200 + i * 20, 300, 20 }, this));
			i++;
		}
		buy = true;
	}
	if (control->id == 70)
	{
		for (ListItem<GuiButton*>* btn = itemsBtns.start; btn != nullptr; btn = btn->next)
		{
			app->guiManager->DestroyGuiControl(btn->data);
		}
		itemsBtns.Clear();
		int i = 0;
		for (ListItem<ItemHolder*>* item = app->entMan->inventory->slots.start; item != nullptr; item = item->next)
		{
			const char* itemName = item->data->item->name.GetString();
			itemsBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 100 + i, itemName, { 500, 200 + i * 20, 300, 20 }, this));
			i++;
		}
		buy = false;
	}
	if (control->id == 71)
	{
		UnShow();
	}
	return true;
}
