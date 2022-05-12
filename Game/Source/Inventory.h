#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "App.h"
#include "List.h"
#include "Player.h"
#include "Scene.h"
#include "Item.h"
#include "Capybara.h"

struct ItemHolder
{
	ItemHolder(Item* item, int num)
	{
		item = this->item;
		cuantity = num;
	}
	bool use(Capybara* capy)
	{
		if (cuantity > 0)
		{
			item->Use(capy);
			cuantity--;
			if (cuantity == 0)
				app->scene->player->GetInventory().DeleteSlot(item);
				
		}
			
	}
	int cuantity;
	Item* item;
};


class Inventory
{
public:
	List<ItemHolder*> slots;

public:

	void DeleteSlot(Item* item)
	{
		ListItem<ItemHolder*>* slot = slots.start;
		while (slot)
		{
			if (slot->data->item == item)
				break;
			slot = slot->next;
		}
		if (!slot)
			slots.Del(slot);
	}
	void AddItem(Item* item)
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
				ItemHolder* newItem = new ItemHolder(item, 1);
				slots.Add(newItem);
			}
			i = i->next;
		}


	}

	
};

#endif // !__INVENTORY_H__
