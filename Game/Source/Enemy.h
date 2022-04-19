#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

#include "List.h"
#include "Animation.h"


class Capybara;

class Enemy : public Entity
{
public:
	Enemy(iPoint position, uint32 id, const char* name);
	~Enemy();

	//Base functions
	bool Update(float dt);
	bool Draw(Render* render);

	void SetCombat(bool value);

	List<Capybara*>& GetBattleTeam();

	//Adds a capybara to the player battle team
	void AddCapybaraToBatle(Capybara* capybara);

private:
	List<Capybara*> battleTeam;
	bool isCombat = false;
};


#endif // !__ENEMY_H__

