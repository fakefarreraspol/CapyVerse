#pragma once

#include "Entity.h"

#include "App.h"
#include "Physics.h"
#include "QuestManager.h"
#include "Animation.h"
#include "Textures.h"

class Bridge : public Entity
{
public:
	Bridge(iPoint position, uint32_t id) : Entity(EntityType::BRIDGE, id, "Door", position)
	{
		currentAnim = &(first);
		first.PushBack({ 0, 0, 236, 146 });
		second.PushBack({ 236, 10, 242, 132 });
		third.PushBack({ 476, 26, 244, 105 });

	}
	~Bridge()
	{

	}
	bool Start()
	{
		if(!collider)
			collider = app->colManager->CreateRectangle(position.x, position.y, 32, 64 + 32, bodyType::STATIC);
		
		return true;
	}
	void Update()
	{
		counter--;

		if (counter == 2)
			currentAnim = &(first);
		if (counter == 1)
			currentAnim = &(second);
		if (counter == 0)
			currentAnim = &(third);
		if (counter <= 0)
		{
			app->colManager->world->DestroyBody(collider->body);
		}
	}

	bool CleanUp()
	{
		app->colManager->world->DestroyBody(collider->body);
		
		return true;
	}
public:
	int counter = 2;
private:
	PhysBody* collider = nullptr;

	Animation first;
	Animation second;
	Animation third;
};