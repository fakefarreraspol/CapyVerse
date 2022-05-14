#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Input.h"
#include "Render.h"

struct Collider;

enum class EntityType
{
	NONE = -1,
	PLAYER,
	CAPYBARA,
	ITEM,
	EQUIPMENT,
	ENEMY,
	NPC
};

class Entity
{
public:

	Entity(EntityType type, uint32 id, const char* name, iPoint position) : type(type), active(true), id(id), position(position)
	{
		this->name.Create("%s_%i", name, id);
	}
	
	iPoint& GetPosition() 
	{
		return position;
	}


	virtual bool Start()
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Draw(Render* render)
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}

	void Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(PhysBody* c1, PhysBody* c2) {

	};

public:

	SString name;
	EntityType type;
	bool active = true;
	uint32 id;            

	iPoint position;
	iPoint speed;
	bool renderable = false;
	SDL_Texture* texture = nullptr;
};

#endif // __ENTITY_H__
