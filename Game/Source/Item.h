#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"

class Item : public Entity
{
public:

	Item(uint32 id, iPoint bounds);
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
};

#endif // __ITEM_H__