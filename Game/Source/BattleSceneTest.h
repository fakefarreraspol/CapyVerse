#ifndef __BATTLESCENE_H__
#define __BATTLESCENE_H__

#include "List.h"

#include "Module.h"

enum class Turn
{
	NONE = -1,
	PLAYER,
	ENEMY
};

class Capybara;

class BattleSceneTest : public Module
{
public:
	BattleSceneTest(bool startEnabled);
	virtual ~BattleSceneTest();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:
	List<Capybara*> enemies;

	Turn turn = Turn::NONE;
};


#endif // !__BATTLESCENE_H__

