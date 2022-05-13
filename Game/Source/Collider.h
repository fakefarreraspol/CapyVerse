#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "Point.h"
#include "List.h"
#define MAX_LISTENERS 5

class Module;
class Entity;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		ORB,
		YELLOW_FLOWER,
		RED_FLOWER,
		STRUCTURE,
		PLAYER,
		NPC,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		BOMB,
		EXPLOSION,
		WIN,
		NEXT,
		MAX,
		POWER_UP,
		BOUNDS
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr, Entity* entity = nullptr);

	void SetPos(int x, int y);

	iPoint GetPos() { return iPoint {rect.x,rect.y}; }
	
	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	
	List<Module*> listeners;
	Entity* entity = nullptr;
};


#endif // !__COLLIDER_H__

