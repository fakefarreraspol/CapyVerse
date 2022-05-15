#ifndef __LEVER_H__
#define __LEVER_H__

#include "Entity.h"

#include "GuiText.h"

class Door;

class Lever : public Entity
{
public:
	Lever(iPoint position, uint32_t id = 0, uint32_t questID = -1);

	~Lever();

	bool Start();

	bool CleanUp();

	void SetListener(Door* listener);
	void SetQuest(uint32_t questID);
	bool Update(float dt);

	void OnCollision(PhysBody* c1, PhysBody* c2);

	bool Draw(Render* render);

private:
	PhysBody* trigger = nullptr;
	PhysBody* collider = nullptr;
	Door* listener = nullptr;

	uint32_t questID;

	bool activated = false;
	bool questTrigger = false;

	GuiText* text = nullptr;
};

#endif // !__LEVER_H__
