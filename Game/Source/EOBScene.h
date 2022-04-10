
#ifndef __EOB_SECENE_H__
#define __EOB_SECENE_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

class Capybara;
class Player;

class EOBScene : public Module
{
public:
	EOBScene(bool startEnabled);

	~EOBScene();


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
	// Called before quitting
	bool CleanUp();

private:
	Player* player = nullptr;
};

#endif // !__EOB_SECENE_H__


