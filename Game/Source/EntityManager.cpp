#include "EntityManager.h"
#include "App.h"

#include "Defs.h"
#include "Log.h"

#include "Player.h"
#include "NPC.h"
#include "Enemy.h"
#include "Trader.h"

#include "Chinabara.h"
#include "Punkibara.h"
#include "Rainbowbara.h"
#include "Retrobara.h"
#include "Emobara.h"
#include "Egirlbara.h"
#include "Pinkbara.h"
#include "Simpbara.h"
#include "Chadbara.h"
#include "Lever.h"
#include "Bridge.h"


#include "Textures.h"
#include "Pause.h"
#include "Item.h"
#include "Items.h"
#include "Animation.h"
#include "Inventory.h"

EntityManager::EntityManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("entity_manager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	inventory = new Inventory();
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

	delete inventory;

	app->tex->UnLoad(texture);
	app->tex->UnLoad(capyTex);
	entities.Clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type, uint32 id, iPoint position, const char* name)
{
	Entity* entity = nullptr;
	
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
	case EntityType::LEVER:
		entity = new Lever(position, id);
		break;
	case EntityType::BRIDGE:
		entity = new Bridge(position, id);
		break;
	case EntityType::TRADER:
		entity = new Trader(position, id, name);
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
	case ItemType::HP_POTION:		item = (Item*) new HpPotion(id, bounds, "HP POTION");			break;
	case ItemType::MP_POTION:		item = (Item*) new MpPotion(id, bounds, "MP POTION");			break;
	case ItemType::REVIVE:			item = (Item*) new Revive(id, bounds, "REVIVE");				break;
	case ItemType::ANTIDOTE:		item = (Item*) new Antidote(id, bounds, "ANTIDOTE");			break;
	case ItemType::ELIXIR_POTION:	item = (Item*) new ElixirPotion(id, bounds, "ELIXIR POTION");	break;
	case ItemType::SPINACH:			item = (Item*) new Spinach(id, bounds, "SPINACH");				break;
	case ItemType::ORANGE:			item = (Item*) new Orange(id, bounds, "ORANGE");				break;
	case ItemType::SPID:			item = (Item*) new Orange(id, bounds, "SPID");					break;


	case ItemType::FREERUNERS_ARMOR:			item = (Item*) new FreeRunersArmor(id, bounds, "FREE RUNER'S ARMOR");			break;
	case ItemType::BOW_SPELLDRINKER:			item = (Item*) new BowSpellDrinker(id, bounds, "BOW SPELLDRINKER");				break;
	case ItemType::ARMOR_VULNERABILITY:			item = (Item*) new ArmorVulnerability(id, bounds, "ARMOR OF VULNERABILITY");	break;
	case ItemType::SCHOLAR_NECKLACE:			item = (Item*) new ScholarNecklace(id, bounds, "SCHOLAR NECKLACE");				break;
	case ItemType::HEAVY_SWORD:					item = (Item*) new HeavySword(id, bounds, "HEAVY SWORD");						break;
	case ItemType::BAMBU_ARMOR:					item = (Item*) new BambuArmor(id, bounds, "BAMBU ARMOR");						break;
	case ItemType::MYSTERY_ARMOR:				item = (Item*) new MysteryArmor(id, bounds, "MYSTERY ARMOR");					break;
	case ItemType::HEALTH_NECKLACE:				item = (Item*) new HealthNecklace(id, bounds, "HEALTH NECKLACE");				break;
	case ItemType::POWER_NECKLACE:				item = (Item*) new PowerNecklace(id, bounds, "POWER NECKLACE");					break;
	case ItemType::LIGHT_NECKLACE:				item = (Item*) new ArmorVulnerability(id, bounds, "LIGHT NECKLACE");			break;
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

Capybara* EntityManager::CreateCapybara(pugi::xml_node& node)
{
	Capybara* entity = nullptr;

	int id = entities.Count();
	iPoint position = { node.attribute("position_x").as_int(),node.attribute("position_y").as_int() };

	SString name = node.attribute("name").as_string();

	if (name == "Chinabara")
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
		entity->LoadState(node);
	}


	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity)
		{
			entities.Del(item);
			break;
		}
			
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if (entity != nullptr) entities.Add(entity);
}

bool EntityManager::Start()
{
	//// inventory test
	Item* uwu01 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::HP_POTION);
	Item* uwu02 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::MP_POTION);
	Item* uwu03 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::REVIVE);
	Item* uwu04 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::FREERUNERS_ARMOR);
	Item* uwu05 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::BOW_SPELLDRINKER);
	Item* uwu06 = app->entMan->CreateEntity(1, { 0,0 }, " ", ItemType::ARMOR_VULNERABILITY);


	inventory->AddItem(uwu01, 1);
	inventory->AddItem(uwu02, 2);
	inventory->AddItem(uwu03, 3);
	inventory->AddItem(uwu04, 3);
	inventory->AddItem(uwu05, 3);
	inventory->AddItem(uwu06, 3);

	texture = app->tex->Load("Assets/Textures/Sprites/characters.png");
	capyTex = app->tex->Load("Assets/Textures/Sprites/capybaras.png");
	itemsTex = app->tex->Load("Assets/Textures/Sprites/items.png");
	props = app->tex->Load("Assets/Textures/Sprites/props.png");

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

	inventory->DeleteEmpty();

	return ret;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	inventory->LoadState(data.child("inventory"));
//
//<<<<<<< HEAD
//	return true;
//=======
//	for (pugi::xml_node entityNode = data.first_child(); entityNode && ret; entityNode = entityNode.next_sibling())
//	{
//		int entityId = entityNode.attribute("id").as_int();
//		ret = entities.At(entityId)->data->LoadState(entityNode);
//		printf("Succesfully loaded entity %s\n", entities.At(entityId)->data->idName.GetString());
//	}
//
//	return ret;
//>>>>>>> development
	return true;
}

bool EntityManager::SaveState(pugi::xml_node& data) const
{
	bool ret = true;

	//ListItem<Entity*>* item = entities.start;
	//while (item != NULL)
	//{
	//	data.append_child(item->data->capyName.GetString());
	//	// = item->data->SaveState(data.child(item->data->name.GetString()));

	//	ret = item->data->SaveState(data.child(item->data->capyName.GetString()));
	//	item = item->next;
	//}

	pugi::xml_node inventoryData = data.append_child("inventory");

	inventory->SaveState(inventoryData);
	

//=======
//	while (item != NULL)
//	{
//		data.append_child(item->data->idName.GetString());
//		// = item->data->SaveState(data.child(item->data->name.GetString()));
//
//		ret = item->data->SaveState(data.child(item->data->idName.GetString()));
//		item = item->next;
//	}
//>>>>>>> development
	return ret;
}

bool EntityManager::Draw() {

	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;
		uint32_t w = pEntity->w;
		uint32_t h = pEntity->h;

		
		SDL_RendererFlip flip = pEntity->faceLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		if (pEntity->active != false)
		{
			if (pEntity->type == EntityType::CAPYBARA)
			{
				ret = app->render->DrawTexture(capyTex, pEntity->GetPosition().x - w / 2, pEntity->GetPosition().y - h / 2,
					&pEntity->currentAnim->GetCurrentFrame(), false, 1.0, flip);
			}
			else if (pEntity->type == EntityType::BRIDGE || pEntity->type == EntityType::LEVER)
			{
				ret = app->render->DrawTexture(props, pEntity->GetPosition().x - w / 2, pEntity->GetPosition().y - h / 2,
					&pEntity->currentAnim->GetCurrentFrame(), false, 1.0, flip);
			}
			else
			{
				ret = app->render->DrawTexture(texture, pEntity->GetPosition().x - w / 2, pEntity->GetPosition().y - h / 2,
					&pEntity->currentAnim->GetCurrentFrame(), false, 1.0, flip);
			}
		}
		
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

Entity* EntityManager::CloneItem(Item* item)
{

	Entity* ret = CreateEntity(item->id, item->position, item->name.GetString(), item->itemType);

	/*Entity* ret = CreateEntity(item->id, item->position, item->idName.GetString(), item->type);*/

	return ret;
}


bool EntityManager::PrintItem(Item* item, int x, int y)
{
	iPoint pos;
	int dim = 64;
	switch (item->itemType)
	{
	case HP_POTION:			pos = { 0,0 };
				  break;
	case MP_POTION:			pos = { 0,1 };
				  break;
	case REVIVE:			pos = { 0,5 };
			   break;
	case ANTIDOTE:			pos = { 0,6 };
				 break;
	case ELIXIR_POTION:		pos = { 0,7 };
					  break;
	case SPINACH:			pos = { 0,8 };
				break;
	case ORANGE:			pos = { 1,7 };
			   break;
	case SPID:				pos = { 1,9 };
			 break;
	case FREERUNERS_ARMOR:	pos = { 1,0 };
						 break;
	case BOW_SPELLDRINKER:	pos = { 1,1 };
						 break;
	case ARMOR_VULNERABILITY:	pos = { 1,2 };
							break;
	case SCHOLAR_NECKLACE:	pos = { 0,2 };
						 break;
	case HEAVY_SWORD:		pos = { 1,4 };
					break;
	case BAMBU_ARMOR:		pos = { 1,5 };
					break;
	case MYSTERY_ARMOR:		pos = { 1,6 };
					  break;
	case HEALTH_NECKLACE:	pos = { 1,7 };
						break;
	case POWER_NECKLACE:	pos = { 0,3 };
					   break;
	case LIGHT_NECKLACE:	pos = { 0,4 };
					   break;
	default:
		break;
	}

	SDL_Rect rec = { pos.y * dim, pos.x * dim , dim, dim };

	return app->render->DrawTexture(itemsTex, x, y, &rec,true);
}