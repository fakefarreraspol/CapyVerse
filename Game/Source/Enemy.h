#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "NPC.h"

#include "List.h"
#include "Animation.h"
#include "Dialog.h"

class Capybara;

class Enemy : public NPC
{
public:
	Enemy(iPoint position, uint32 id, const char* name);
	~Enemy();
	bool Start();
	//Base functions
	bool Update(float dt);

	void SetCombat(bool value);

	List<Capybara*>& GetBattleTeam();
	//Adds a capybara to the player battle team
	void AddCapybaraToBatle(Capybara* capybara);

	void OnCollision(PhysBody* c1, PhysBody* c2);

	bool CleanUp();
	bool isBoss = false;
private:
	Animation normalEnemy;
	Animation boss;
	List<Capybara*> battleTeam;
	bool isCombat = false;
	bool load = true;
	bool triggered = false;
};


#endif // !__ENEMY_H__

