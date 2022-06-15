#include "Inventory.h"
#include "Player.h"
#include "Entity.h"

Inventory::Inventory()
{

}
Inventory::~Inventory()
{

}

void Inventory:: DeleteEmpty()
{
	ListItem<ItemHolder*>* slot = slots.start;
	while (slot)
	{
		if (slot->data->cuantity <= 0)
		{
			ListItem<ItemHolder*>* del = slot;
			slot = del->next;

			if (slot->data->item->beingUsed)
				del->data->item = nullptr;

			slots.Del(del);
			continue;
		}
		slot = slot->next;
	}

}

void Inventory::AddItem(Item* item, int n)
{
	ListItem<ItemHolder*>* i = slots.start;

	if (i == nullptr)
	{
		ItemHolder* newItem = new ItemHolder(item, n);
		slots.Add(newItem);
	}

	while (i)
	{
		if (i->data->item->itemType == item->itemType)
		{
			i->data->cuantity++;
			break;
		}
		if (i == slots.end)
		{
			ItemHolder* newItem = new ItemHolder(item, n);
			slots.Add(newItem);
		}
		i = i->next;
	}


}

void Inventory::DelItem(Item* item, int n)
{
	ListItem<ItemHolder*>* i = slots.start;
	while (i)
	{
		if (i->data->item->itemType == item->itemType)
			i->data->cuantity -= n;
		i = i->next;
	}
}

bool Inventory::CleanUp()
{
	ListItem<ItemHolder*>* i = slots.start;
	while (i)
	{
		app->entMan->DestroyEntity(i->data->item);
		i = i->next;
	}
	slots.Clear();
	return true;
}

bool Inventory::UseItem(Item* item, Capybara* capy)
{
	bool ret = true;

	Item* n = (Item*)app->entMan->CloneItem(item);
	capy->consumables.Add(n);
	n->Use(capy);
	
	DelItem(item);
	DeleteEmpty();

	return ret;
}

bool Inventory::EquipItem(Item* item, Capybara* capy)
{
	Item* n = (Item*)app->entMan->CloneItem(item);
	capy->EquipItem(n);

	DelItem(item);
	DeleteEmpty();

	return true;
}

bool Inventory::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	CleanUp();

	for (pugi::xml_node slotNode = data.first_child(); slotNode && ret; slotNode = slotNode.next_sibling())
	{
		uint32 id = 1;
		int num = slotNode.attribute("quantity").as_int();
		ItemType type = (ItemType)slotNode.attribute("type").as_int();

		Item* item = app->entMan->CreateEntity(id, { 0,0 }, "", type);

		AddItem(item, num);
		printf("Succesfully loaded item %s\n", item->name.GetString());
	}
	

	return true;
}
bool Inventory::SaveState(pugi::xml_node& data) const
{
	ListItem<ItemHolder*> *slot = slots.start;

	while (slot != NULL)
	{
		pugi::xml_node itemData = data.append_child("item");
		itemData.append_attribute("type").set_value(slot->data->item->itemType);
		itemData.append_attribute("quantity").set_value(slot->data->cuantity);

		slot = slot->next;
	}

	return true;
}