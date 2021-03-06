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
		if (i->data->item->type == item->type)
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
		if (i->data->item->type == item->type)
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
