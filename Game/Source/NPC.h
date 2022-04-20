#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"
#include "Dialog.h"
#include "SDL_image/include/SDL_image.h"

class NPC : public Entity
{
public:

	Collider* collider = nullptr;
	Dialog* dialog;
	bool load = true;
public:

	NPC(iPoint position, uint32 id, const char* name);
	~NPC();

	//Base functions
	bool Start();
	bool Update(float dt);
	bool Draw(Render* render);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	void OnCollision(Collider* c1, Collider* c2);

	bool CleanUp();
	
};

#endif