
#ifndef __EOB_SECENE_H__
#define __EOB_SECENE_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiBar.h"
#include "List.h"
#include "GuiText.h"

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

	void SetXP(int xp);
	// Called before all Updates
	bool PostUpdate();
	// Called before quitting
	bool CleanUp();

	bool playerWin = false;
private:
	int counter = 100;
	Player* player = nullptr;
	List<GuiBar*> bars;
	List<GuiText*> texts;
	List<GuiText*> lvls;
	List<GuiText*> lvlUp;
	int XP = 0;

	SDL_Texture* capybaras;
	SDL_Texture* win;
	SDL_Texture* lose;
};

#endif // !__EOB_SECENE_H__


