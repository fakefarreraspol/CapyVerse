#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"

#include "List.h"

#include "Capybara.h"

class Textures;
class Audio;
class Collisions;
class PathFinding;
class Render;

class EntityManager : public Module
{
public:

	EntityManager(bool startEnabled);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt);

	bool Draw();

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Entity* CreateEntity(EntityType entityType, uint32 id, iPoint position, const char* name);
	Capybara* CreateEntity(CapybaraType capybaraType, uint32 id, iPoint position, const char* name);

	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

	bool UpdateAll(float dt, bool doLogic);

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data);

public:

	List<Entity*> entities;

	Input* input;
	Textures* tex;
	Audio* audio;
	Collisions* collisions;
	PathFinding* path;
	Render* render;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __ENTITY_MANAGER__

