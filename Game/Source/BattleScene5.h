#ifndef __BATTLESCENE5_H__
#define __BATTLESCENE5_H__

#include "Module.h"
#include "Textures.h"
class Enemy;

class BattleScene5 : public Module
{
public:
	BattleScene5(bool startEnabled);
	virtual ~BattleScene5();

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
