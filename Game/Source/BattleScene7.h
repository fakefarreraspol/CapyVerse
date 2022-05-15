#ifndef __BATTLESCENE7_H__
#define __BATTLESCENE7_H__

#include "Module.h"
#include "Textures.h"
class Enemy;

class BattleScene7 : public Module
{
public:
	BattleScene7(bool startEnabled);
	virtual ~BattleScene7();

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
