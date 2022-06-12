#include "Shop.h"
#include "App.h"
#include "Scene.h"
#include "EntityManager.h"
#include "GuiManager.h"

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
		itemsBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, itemName, { 500, 200 + i * 20, 300, 20 }, this));
		i++;
	}

	buyBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Buy", { 450, 150, 100, 20 }, this);
	sellBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Sell", { 650, 150, 100, 20 }, this);

	return true;
}

bool Shop::PreUpdate()
{
	return true;
}

bool Shop::Update(float dt)
{
	return true;
}

void Shop::Show()
{
}

void Shop::UnShow()
{
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
	return true;
}
