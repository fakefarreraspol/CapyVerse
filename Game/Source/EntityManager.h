#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"

#include "List.h"

#include "Capybara.h"
#include "Item.h"

struct SDL_Texture;
class Textures;
class Audio;
class PhysBody;
class PathFinding;
class Render;
class Inventory;

class EntityManager : public Module
{
public:

	EntityManager(bool startEnabled);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Start();

	bool Update(float dt);

	bool Draw();

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Entity* CreateEntity(EntityType entityType, uint32 id, iPoint position, const char* name);
	Item* CreateEntity(uint32 id, iPoint bounds, const char* name, ItemType type);
	Capybara* CreateEntity(CapybaraType capybaraType, uint32 id, iPoint position, const char* name);

	Entity* CloneItem(Item* item);

	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

	bool UpdateAll(float dt, bool doLogic);
	void OnCollision(PhysBody* c1, PhysBody* c2);

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

public:

	List<Entity*> entities;

	Input* input;
	Textures* tex;
	Audio* audio;
	PhysBody* collisions;
	PathFinding* path;
	Render* render;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	SDL_Texture* capyTex = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* props = nullptr;
	Inventory* inventory;

	int ticks = 0;
	int lastTicks = 0;
};

#endif // __ENTITY_MANAGER__

