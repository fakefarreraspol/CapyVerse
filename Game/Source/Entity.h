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
	EQUIPMENT
};

class Entity
{
public:

	Entity(EntityType type) : type(type), active(true) {}

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

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(Collider* c1, Collider* c2) {

	};

public:

	SString name;
	EntityType type;
	bool active = true;
	uint32 id;            

	iPoint position;
	bool renderable = false;
	SDL_Texture* texture;
};

#endif // __ENTITY_H__