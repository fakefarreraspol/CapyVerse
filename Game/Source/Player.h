#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "List.h"

#include "Entity.h"
#include "Capybara.h"
#include "Collider.h"
#include "Animation.h"


class Player : public Entity
{
public:
	Player(iPoint position, uint32 id, const char* name);
	~Player();

	iPoint lastPos;
	int wallsDetected;
	int lastKeyPressed = 0;
	bool canMove = true;
	float speed = 0.1;
	//Base functions
	bool Update(float dt);
	void UpdateCamera();
	bool Draw(Render* render);
	bool Start();
	//Adds a capybara to the player team 
	void AddCapybara(Capybara* capybara);
	//Adds a capybara to the player battle team
	void AddCapybaraToBatle(Capybara* capybara);

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

	Collider* collider = nullptr;

	void SetCombat(bool value);

	bool isWalking = false;
	void OnCollision(Collider* c1, Collider* c2);
	bool CleanUp();
	SDL_Rect playerIddle = { 0,0,66,66 };
	/*SDL_Rect playerWalkRight[4];*/
	
private:
	int money;

	bool isBattle = false;
	bool isStuck = false;

	Animation* currentAnim = nullptr;

	List<Capybara*> battleTeam;
	List<Capybara*> team;
	bool load = true;
};


#endif // !__PLAYER_H__
