#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

#include "Dialog.h"

struct SDL_Texture;

class Capybara;
class Player;

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

	// Called before all Updates
	bool PostUpdate();
	void OnCollision(Collider* c1, Collider* c2);
	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* img = nullptr;

	GuiButton* btn1 = nullptr;
	GuiSlider* slider1 = nullptr;
	GuiCheckBox* box1 = nullptr;

	Player* player = nullptr;

public:
	Dialog* dialogTest;

};

#endif // __SCENE_H__