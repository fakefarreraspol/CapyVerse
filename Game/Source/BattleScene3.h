#ifndef __BATTLESCENE3_H__
#define __BATTLESCENE3_H__

#include "Module.h"
#include "Textures.h"
class Enemy;

class BattleScene3 : public Module
{
public:
	BattleScene3(bool startEnabled);
	virtual ~BattleScene3();

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
	int SFXchirp;
};


#endif

