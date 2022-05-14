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
		if (slot->data->cuantity == 0)
		{
			ListItem<ItemHolder*>* del = slot;
			slot = del->next;
			slots.Del(del);
			continue;
		}
		slot = slot->next;
	}

}

void Inventory::AddItem(Item* item, int n)
{
	ListItem<ItemHolder*>* i = slots.start;

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