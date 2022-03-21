#include "ModuleCollisions.h"

#include "App.h"
#include "Log.h"
#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::EXPLOSION][Collider::Type::WALL] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RED_FLOWER] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::YELLOW_FLOWER] = true;

	matrix[Collider::Type::BOMB][Collider::Type::WALL] = true;
	matrix[Collider::Type::BOMB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOMB][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BOMB][Collider::Type::RED_FLOWER] = true;
	matrix[Collider::Type::BOMB][Collider::Type::YELLOW_FLOWER] = true;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			if (colliders[i]->pendingToDelete == true) {
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}



bool ModuleCollisions::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::WALL: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;			
			case Collider::Type::ORB: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 155, alpha);
			break;
			case Collider::Type::YELLOW_FLOWER: // yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::RED_FLOWER: // orange
			app->render->DrawRectangle(colliders[i]->rect, 255, 122, 0, alpha);
			break;
			case Collider::Type::STRUCTURE: // purple
			app->render->DrawRectangle(colliders[i]->rect, 122, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::BOMB: // red/white
			app->render->DrawRectangle(colliders[i]->rect, 255, 102, 102, alpha);
			break;
			case Collider::Type::EXPLOSION: // red/white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::ENEMY: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::WIN: // GREEN
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::NEXT: // Pink
			app->render->DrawRectangle(colliders[i]->rect, 255, 125, 0, alpha);
			break;
			case Collider::Type::BOUNDS: // Black
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}