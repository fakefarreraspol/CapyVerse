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

class BattleScene : public Module
{
public:
	BattleScene(bool startEnabled);
	virtual ~BattleScene();

	bool Start();

	bool PreUpdate();

	virtual bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:
	List<Capybara*> enemies;

	Turn turn = Turn::NONE;
};


#endif // !__BATTLESCENE_H__

