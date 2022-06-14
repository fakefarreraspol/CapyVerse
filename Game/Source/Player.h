#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "List.h"

#include "Entity.h"
#include "Capybara.h"
#include "Physics.h"
#include "Animation.h"
#include "Inventory.h"

class Player : public Entity
{
public:
	Player(iPoint position, uint32 id, const char* name);
	~Player();

	iPoint lastPos;
	int wallsDetected;
	int lastKeyPressed = 0;
	bool canMove = true;
	//Base functions
	bool Update(float dt);
	void Debug();
	void UpdateCamera();

	bool Start();
	//Adds a capybara to the player team 
	void AddCapybara(Capybara* capybara);
	//Adds a capybara to the player battle team
	void AddCapybaraToBatle(Capybara* capybara);
	void ChangeCapybaras(Capybara* fromTeam, Capybara* fromBattleTeam);


	//TODO: Update the player input and move the player
	void UpdateInput(float dt);
	iPoint PositionGetterxd()
	{
		return position;
	}
	//Getters for the teams
	List<Capybara*>& GetBattleTeam();
	List<Capybara*>& GetTeam();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	PhysBody* collider = nullptr;

	void SetCombat(bool value);
	void OnCollision(PhysBody* c1, PhysBody* c2);
	bool CleanUp();


	int money = 0;
private:

	bool isBattle = false;
	bool isStuck = false;

	Animation idle;
	Animation walkRight;
	Animation walkLeft;
	Animation walkUp;
	Animation walkDown;

	List<Capybara*> battleTeam;
	List<Capybara*> team;
	bool load = true;

	float32 velocity = 2.0f;


	bool initDebug = false;
};


#endif // !__PLAYER_H__
