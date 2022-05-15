#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

#include "Dialog.h"

struct SDL_Texture;

class Bridge;
class Capybara;
class Player;
class Lever;
class NPC;

class Scene : public Module
{
public:

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void OnCollision(PhysBody* c1, PhysBody* c2);
	// Called before all Updates
	bool PostUpdate();
	// Called before quitting
	bool CleanUp();

public:
	List<NPC*> NPCs;
	List<Lever*> levers;
	Bridge* bridge = nullptr;
	Player* player = nullptr;
	bool load = false;
	bool end = true;
};

#endif // __SCENE_H__