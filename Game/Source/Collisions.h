#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#include "Module.h"
#include "Collider.h"
#include "List.h"

class Entity;

class Collisions : public Module
{
public:
	// Constructor
	// Fills all collision matrix data
	Collisions(bool startEnabled);

	// Destructor
	~Collisions();

	// Called at the beginning of the application loop
	// Removes all colliders pending to delete
	// Checks for new collisions and calls its listeners
	
	
	bool PreUpdate();

	
	// Called at the middle of the application loop
	// Switches the debug mode on/off
	bool Update();

	// Called at the end of the application loop
	// Draw all colliders (if debug mode is enabled)
	
	
	
	bool PostUpdate();

	
	
	
	// Removes all existing colliders
	bool CleanUp();

	// Adds a new collider to the list
	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr, Entity* entity = nullptr);

	// Removes the collider memory and removes it from the colliders array
	void RemoveCollider(Collider* collider);

	// Draws all existing colliders with some transparency
	void DebugDraw();

private:
	// All existing colliders in the scene
	List<Collider*> colliders;

	// The collision matrix. Defines the interaction for two collider types
	// If set to false, collider 1 will ignore collider 2
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];

	// Simple debugging flag to draw all colliders
	bool debug = true;
};

#endif // __MODULE_COLLISIONS_H__