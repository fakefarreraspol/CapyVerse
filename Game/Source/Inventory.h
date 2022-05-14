#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "App.h"
#include "List.h"
#include "Item.h"
#include "Capybara.h"
#include "EntityManager.h"

struct ItemHolder
{

	int cuantity;
	Item* item;

	ItemHolder(Item* item, int num) : item(item), cuantity(num)
	{
	}
	~ItemHolder()
	{
		app->entMan->DestroyEntity(item);
		item = nullptr;
	}
	bool use(Capybara* capy)
	{
		if (cuantity > 0)
		{
			item->Use(capy);
			cuantity--;

		}
		return true;
	}


};

class Inventory
{
public:
	List<ItemHolder*> slots;
public:
	Inventory();
	~Inventory();
	void DeleteEmpty();
	void AddItem(Item* item, int n);
	bool CleanUp();

	
};

#endif // !__INVENTORY_H__
