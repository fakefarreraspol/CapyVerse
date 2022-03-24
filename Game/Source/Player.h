#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "List.h"

#include "Entity.h"
#include "Capybara.h"

class Player : public Entity
{
public:
	Player(iPoint position, uint32 id, const char* name);
	~Player();

	//Base functions
	bool Update(float dt);
	bool Draw(Render* render);

	//Adds a capybara to the player team 
	void AddCapybara(Capybara* capybara);
	//Adds a capybara to the player battle team
	void AddCapybaraToBatle(Capybara* capybara);

	//TODO: Update the player input and move the player
	void UpdateInput();

	//Getters for the teams
	List<Capybara*> GetBattleTeam();
	List<Capybara*> GetTeam();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

private:
	int money;
	
	List<Capybara*> battleTeam;
	List<Capybara*> team;
};


#endif // !__PLAYER_H__
