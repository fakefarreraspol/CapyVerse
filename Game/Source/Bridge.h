#pragma once

#include "Entity.h"

#include "App.h"
#include "Physics.h"
#include "QuestManager.h"
#include "Animation.h"
#include "Textures.h"

class Door : public Entity
{
public:
	Door(iPoint position, uint32_t id) : Entity(EntityType::DOOR, id, "Door", position)
	{
		anim = &first;
	}
	~Door()
	{

	}
	bool Start()
	{
		if(!collider)
			collider = app->colManager->CreateRectangle(position.x, position.y, 32, 64, bodyType::STATIC);

		app->tex->Load("Assets/Textures/Sprites/props.png");
	}
	void Update()
	{
		counter--;

		if (counter == 2)
			anim = &first;
		if (counter == 1)
			anim = &second;
		if (counter == 0)
			anim = &third;
		if (counter <= 0)
		{
			app->colManager->world->DestroyBody(collider->body);
		}
	}

	bool Draw(Render* render)
	{
		render->DrawTexture(texture, position.x + 32, position.y, &anim->GetCurrentFrame());
	}

	bool CleanUp()
	{
		app->colManager->world->DestroyBody(collider->body);
		app->tex->UnLoad(texture);
	}
public:
	int counter;
private:
	PhysBody* collider;
	Animation* anim;
	Animation first;
	Animation second;
	Animation third;
};