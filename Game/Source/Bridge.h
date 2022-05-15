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
		anim = &first;
		first.PushBack({ 0, 0, 236, 146 });
		second.PushBack({ 236, 10, 242, 132 });
		third.PushBack({ 476, 26, 244, 105 });

		/*if (!collider)
			collider = app->colManager->CreateRectangle(position.x, position.y, 32, 64, bodyType::STATIC);
		if (!texture)
			texture = app->tex->Load("Assets/Textures/Sprites/props.png");*/
	}
	~Bridge()
	{

	}
	bool Start()
	{
		if(!collider)
			collider = app->colManager->CreateRectangle(position.x, position.y, 32, 64 + 32, bodyType::STATIC);
		
		texture =app->tex->Load("Assets/Textures/Sprites/props.png");
		return true;
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
		render->DrawTexture(texture, position.x, position.y - 64, &anim->GetCurrentFrame());
		return true;
	}

	bool CleanUp()
	{
		app->colManager->world->DestroyBody(collider->body);
		app->tex->UnLoad(texture);
		return true;
	}
public:
	int counter = 2;
private:
	PhysBody* collider = nullptr;

	Animation* anim;
	Animation first;
	Animation second;
	Animation third;
};