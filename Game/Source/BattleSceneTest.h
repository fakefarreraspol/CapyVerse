#ifndef __BATTLESCENE_H__
#define __BATTLESCENE_H__

#include "List.h"

#include "Render.h"
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
class GuiText;
class GuiBar;

class BattleSceneTest : public Module
{
public:
	BattleSceneTest(bool startEnabled);
	virtual ~BattleSceneTest();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	void CreateAttackMenu();

	void ShowAttackMenu();

	void ShowAbilityMenu();

	void UpdateInput();

	bool PostUpdate();

	bool CleanUp();

	void SetPlayer(Player* player);

	void SetEnemy();

	void CreateTexts();

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	List<Capybara*> enemies;
	List<Capybara*> playerTeam;

	Player* player;


	ListItem<Capybara*>* currentCapybara = nullptr;	//The capybara that the turn is on
	ListItem<Capybara*>* selectedCapybara = nullptr;	//The capybara wich the action may take effect
	
	GuiButton* attackBtn = nullptr;
	GuiButton* abilityBtn = nullptr;
	GuiButton* inventoryBtn = nullptr;
	GuiButton* runBtn = nullptr;

	List<GuiButton*> attackBtns;
	List<GuiText*> enemyInfo;
	List<GuiBar*> enemyBars;

	List<GuiText*> playerNames;
	List<GuiBar*>  playerBars;
	List<GuiText*> playerHeathText;
	GuiText* currentName = nullptr;

	bool updateInput = true;

	bool showAttackMenu = false;
	bool showAbilityMenu = false;
	bool createAttackMenu = false;
	bool createTexts = false;
	bool updateCurrentName = false;

	Turn turn = Turn::NONE;
};


#endif // !__BATTLESCENE_H__

