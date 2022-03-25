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

class Player;
class GuiButton;
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

	void ShowAttackMenu();

	void ShowAbilityMenu();

	void UpdateInput();

	bool PostUpdate();

	bool CleanUp();

	void SetPlayer(Player* player);

	void SetEnemy();

private:
	List<Capybara*> enemies;
	List<Capybara*> playerTeam;

	Player* player;


	ListItem<Capybara*>* currentCapybara;	//The capybara that the turn is on
	ListItem<Capybara*>* selectedCapybara;	//The capybara wich the action may take effect
	
	GuiButton* attackBtn = nullptr;
	GuiButton* abilityBtn = nullptr;
	GuiButton* inventoryBtn = nullptr;
	GuiButton* runBtn = nullptr;

	bool updateInput = true;

	bool showAttackMenu = false;
	bool showAbilityMenu = false;


	Turn turn = Turn::NONE;
};


#endif // !__BATTLESCENE_H__

