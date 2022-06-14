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
		CleanUp();
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
	void CleanUp()
	{
		app->entMan->DestroyEntity((Entity*)item);
		item = nullptr;
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
	void AddItem(Item* item, int n=1);
	void DelItem(Item* item, int n=1);
	bool CleanUp();

	bool UseItem(Item* item, Capybara* capy);
	bool EquipItem(Item* item, Capybara* capy);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
};

#endif // !__INVENTORY_H__
