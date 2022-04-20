#ifndef __BATTLESCENE2_H__
#define __BATTLESCENE2_H__

#include "Module.h"

class Enemy;

class BattleScene2 : public Module
{
public:
	BattleScene2(bool startEnabled);
	virtual ~BattleScene2();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool CleanUp();

private:
	Enemy* enemy;

public:
	int randomNum = 0;
};


#endif