#ifndef __LEVER_H__
#define __LEVER_H__

#include "Entity.h"
#include "Animation.h"
#include "GuiText.h"

class Bridge;

class Lever : public Entity
{
public:
	Lever(iPoint position, uint32_t id = 0, uint32_t questID = -1);

	~Lever();

	bool Start();

	bool CleanUp();

	void SetListener(Bridge* listener);
	void SetQuest(uint32_t questID);
	bool Update(float dt);

	void OnCollision(PhysBody* c1, PhysBody* c2);

	bool Draw(Render* render);


public:
	bool activated = false;
	Animation* anim;
	Animation open;
	Animation closed;
private:
	PhysBody* trigger = nullptr;
	PhysBody* collider = nullptr;
	Bridge* listener = nullptr;

	uint32_t questID;

	

	bool questTrigger = false;
};

#endif // !__LEVER_H__
