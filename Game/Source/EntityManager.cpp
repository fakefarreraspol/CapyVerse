#include "EntityManager.h"
#include "App.h"

#include "Defs.h"
#include "Log.h"

#include "Player.h"
#include "NPC.h"
#include "Enemy.h"

#include "Chinabara.h"
#include "Punkibara.h"
#include "Rainbowbara.h"
#include "Retrobara.h"
#include "Emobara.h"
#include "Egirlbara.h"
#include "Pinkbara.h"
#include "Simpbara.h"
#include "Chadbara.h"
#include "Textures.h"
#include "Pause.h"
#include "Item.h"
#include "Items.h"

EntityManager::EntityManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	//L13: TODO 6: Initialize Entities from XML 
	
	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.Clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type, uint32 id, iPoint position, const char* name)
{
	Entity* entity = nullptr;
	if(id == 0)
		id = entities.Count();

	switch (type)
	{
	case EntityType::NONE:
		break;
	case EntityType::PLAYER:
		entity = new Player(position, id, name);
		break;
	case EntityType::EQUIPMENT:
		break;
	case EntityType::ENEMY:
		entity = new Enemy(position, id, name);
		break;
	case EntityType::NPC:
		entity = new NPC(position, id, name);
		break;
	default:
	{
		LOG("ERROR: Entity with no type couldn't be created");
	}break;
	}

	if (entity != nullptr)
		AddEntity(entity);

	return entity;
}

Item* EntityManager::CreateEntity(uint32 id, iPoint bounds, const char* name, ItemType type)
{
	Item* item = nullptr;
	switch (type)
	{
	case ItemType::HP_POTION:		item = (Item*) new HpPotion(id, bounds, "HP POTION");		break;
	case ItemType::MP_POTION:		item = (Item*) new MpPotion(id, bounds, "MP POTION");		break;
	case ItemType::REVIVE:			item = (Item*) new Revive(id, bounds, "REVIVE");			break;
	}

	if (item!=nullptr)
	{
		AddEntity(item);
		item->Start();
	}
		
	return item;
}

Capybara* EntityManager::CreateEntity(CapybaraType capybaraType, uint32 id, iPoint position, const char* name)
{
	Capybara* entity = nullptr;

	id = entities.Count();

	if(name == "Chinabara")
		entity = new Chinabara(id, position);
	if (name == "Punkibara")
		entity = new Punkibara(id, position);
	if (name == "Rainbowbara")
		entity = new Rainbowbara(id, position);
	if (name == "Retrobara")
		entity = new Retrobara(id, position);
	if (name == "Emobara")
		entity = new Emobara(id, position);
	if (name == "Egirlbara")
		entity = new Egirlbara(id, position);
	if (name == "Pinkbara")
		entity = new Pinkbara(id, position);
	if (name == "Simpbara")
		entity = new Simpbara(id, position);
	if (name == "Chadbara")
		entity = new Chadbara(id, position);


	if (entity != nullptr)
	{
		AddEntity(entity);
		entity->Start();
	}

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.Del(item);
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if (entity != nullptr) entities.Add(entity);
}

bool EntityManager::Start()
{
	
	return true;
}

bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	if(!app->pause)
		UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	Draw();

	return true;
}

bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	if (doLogic)
	{
		for (item = entities.start; item != NULL && ret == true; item = item->next)
		{
			pEntity = item->data;

			if (pEntity->active == false) continue;
			ret = item->data->Update(dt);
		}
	}

	return ret;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	for (pugi::xml_node entityNode = data.first_child(); entityNode && ret; entityNode = entityNode.next_sibling())
	{
		int entityId = entityNode.attribute("id").as_int();
		ret = entities.At(entityId)->data->LoadState(entityNode);
	}

	/*ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->LoadState(data.child(item->data->name.GetString()));
		item = item->next;
	}*/

	return ret;
}

bool EntityManager::SaveState(pugi::xml_node& data) const
{
	bool ret = true;

	ListItem<Entity*>* item = entities.start;

	while (item != NULL)
	{
		data.append_child(item->data->name.GetString());
		// = item->data->SaveState(data.child(item->data->name.GetString()));

		ret = item->data->SaveState(data.child(item->data->name.GetString()));
		item = item->next;
	}


	

	return ret;
}

bool EntityManager::Draw() {

	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Draw(app->render);
		
	}

	return ret;
}

void EntityManager::OnCollision(PhysBody* c1, PhysBody* c2)
{

	if (c1->eListener != nullptr)
		if (c1->eListener->active == true)
			c1->eListener->OnCollision(c1, c2);

	if (c2->eListener != nullptr)
		if (c2->eListener->active == true)
			c2->eListener->OnCollision(c2, c1);
}