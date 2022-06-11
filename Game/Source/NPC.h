#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"
#include "Dialog.h"
#include "SDL_image/include/SDL_image.h"
class PhysBody;
class NPC : public Entity
{
public:

	NPC(iPoint position, uint32 id, const char* name);
	~NPC();

	//Base functions
	bool Start();
	bool Update(float dt);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	void OnCollision(PhysBody* c1, PhysBody* c2);

	bool CleanUp();
public:
	uint16_t triggerCounter = 120;
	SString NPCname;
	PhysBody* trigger = nullptr;
	PhysBody* collider = nullptr;
	Dialog* dialog;
	bool load = true;
	int questID;
};

#endif