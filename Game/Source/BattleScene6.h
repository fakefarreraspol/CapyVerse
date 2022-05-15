#ifndef __BATTLESCENE6_H__
#define __BATTLESCENE6_H__

#include "Module.h"
#include "Textures.h"
class Enemy;

class BattleScene6 : public Module
{
public:
	BattleScene6(bool startEnabled);
	virtual ~BattleScene6();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool CleanUp();

private:
	Enemy* enemy;

public:
	int randomNum = 0;
	SDL_Texture* background;
};


#endif

