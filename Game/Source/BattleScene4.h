#ifndef __BATTLESCENE4_H__
#define __BATTLESCENE4_H__

#include "Module.h"
#include "Textures.h"

class Enemy;
class BattleScene4 : public Module
{
public:
	BattleScene4(bool startEnabled);
	virtual ~BattleScene4();

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