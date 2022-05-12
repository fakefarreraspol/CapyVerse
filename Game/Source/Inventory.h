#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "List.h"
#include "Item.h"
struct ItemHolder
{
	int cuantity;
	Item* item;
};


class Inventory
{
public:

	ListItem<ItemHolder*> slots;


};

#endif // !__INVENTORY_H__
