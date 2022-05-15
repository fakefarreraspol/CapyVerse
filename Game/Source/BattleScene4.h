#ifndef __BATTLESCENE1_H__
#define __BATTLESCENE1_H__

#include "Module.h"
#include "Textures.h"

class Enemy;
class BattleScene1 : public Module
{
public:
	BattleScene1(bool startEnabled);
	virtual ~BattleScene1();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool CleanUp();
	 
private:
	Enemy* enemy;
	SDL_Texture* background;

public: 
	int randomNum = 0;
};


#endif