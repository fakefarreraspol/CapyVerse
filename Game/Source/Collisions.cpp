#include "Collisions.h"

#include "App.h"
#include "Log.h"
#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"


Collisions::Collisions(bool startEnabled) : Module(startEnabled)
{
	/*for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;*/
	
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
Collisions::~Collisions()
{

}

bool Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (ListItem<Collider*>* i = colliders.start; i !=nullptr;  i = i->next)
	{
		if (i->data != nullptr && i->data->pendingToDelete == true)
		{
			colliders.Del(i);
		}
	}

	Collider* c1;
	Collider* c2;

	for (ListItem<Collider*>* i = colliders.start; i != nullptr; i = i->next)
	{
		c1 = i->data;

		// avoid checking collisions already checked
		for (ListItem<Collider*>* k = i->next; k != nullptr; k = k->next)
		{

			c2 = k->data;

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (ListItem<Module*>* m = c1->listeners.start; m != nullptr; m = m->next)
					if (m->data != nullptr)m->data->OnCollision(c1, c2);

				for (ListItem<Module*>* m = c2->listeners.start; m != nullptr; m = m->next)
					if (m->data != nullptr)m->data->OnCollision(c2, c1);
			}
		}
	}
	

	return true;
}



bool Collisions::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	return true;
}

bool Collisions::PostUpdate()
{
	if (app->GetDebug())
		DebugDraw();

	return true;
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (ListItem<Collider*>* temp = colliders.start; temp != nullptr; temp = temp->next)
	{
		if (temp->data == nullptr) continue;
		switch (temp->data->type)
		{
			case Collider::Type::NONE: // white
			app->render->DrawRectangle(temp->data->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::WALL: // blue
			app->render->DrawRectangle(temp->data->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::ORB: // blue
			app->render->DrawRectangle(temp->data->rect, 0, 255, 155, alpha);
			break;
			case Collider::Type::YELLOW_FLOWER: // yellow
			app->render->DrawRectangle(temp->data->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::RED_FLOWER: // orange
			app->render->DrawRectangle(temp->data->rect, 255, 122, 0, alpha);
			break;
			case Collider::Type::STRUCTURE: // purple
			app->render->DrawRectangle(temp->data->rect, 122, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(temp->data->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::BOMB: // red/white
			app->render->DrawRectangle(temp->data->rect, 255, 102, 102, alpha);
			break;
			case Collider::Type::EXPLOSION: // red/white
			app->render->DrawRectangle(temp->data->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::ENEMY: // red
			app->render->DrawRectangle(temp->data->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			app->render->DrawRectangle(temp->data->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			app->render->DrawRectangle(temp->data->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::WIN: // GREEN
			app->render->DrawRectangle(temp->data->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::NEXT: // Pink
			app->render->DrawRectangle(temp->data->rect, 255, 125, 0, alpha);
			break;
			case Collider::Type::BOUNDS: // Black
			app->render->DrawRectangle(temp->data->rect, 0, 0, 0, alpha);
			break;

		}

	}
	
}

// Called before quitting
bool Collisions::CleanUp()
{
	LOG("Freeing all colliders");
	for (ListItem<Collider*>* temp = colliders.start; temp != nullptr; temp = temp->next)
	{
		if (temp->data != nullptr)
		{
			RemoveCollider(temp->data);
		}
	}
	

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	/*for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}*/
	ret = new Collider(rect, type, listener);
	colliders.Add(ret);
	return ret;
}

void Collisions::RemoveCollider(Collider* collider)
{
	
	for (ListItem<Collider*>* c = colliders.start; c != nullptr; c = c->next)
	{
		if (c->data == collider)
		{
			colliders.Del(c);
			return;
		}
	}
}