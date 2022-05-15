#pragma once

#include "Entity.h"

class Door : public Entity
{
public:
	Door(iPoint position, uint32_t id) : Entity(EntityType::DOOR, id, "Door", position)
	{

	}



private:

};