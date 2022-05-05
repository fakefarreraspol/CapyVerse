#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"

enum ItemType
{
	CONSUMABLE,
	EQUIPMENT
};

enum ItemName
{
	
};

class Item : public Entity
{
public:

	Item(uint32 id, iPoint bounds, const char* name);
	virtual ~Item();

	bool Update(float dt);
		
	bool Draw(Render* render);

	bool CleanUp();
	
	bool GetPicked();

	void Pick();

	void UnPick();

	void Use();

private:

	bool isPicked = false;
	Entity* entity = nullptr;
};

#endif // __ITEM_H__