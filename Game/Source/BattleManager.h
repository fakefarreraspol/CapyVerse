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
class Enemy;

class BattleManager : public Module
{
public:
	BattleManager(bool startEnabled);
	virtual ~BattleManager();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	void Draw();

	void UpdateInfo();

	void CreateAttackMenu();

	void ShowAttackMenu();

	void ShowAbilityMenu();

	void UpdateInput();

	bool PostUpdate();

	bool CleanUp();

	void SetPlayer(Player* player);

	void SetEnemy(Enemy* enemy);
	void SetTurn(Turn turn);
	Turn GetTurn();

	void CreateTexts();

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	List<Capybara*> enemies;
	List<Capybara*> playerTeam;

	Player* player = nullptr;
	Enemy* enemy = nullptr;


	ListItem<Capybara*>* currentCapybara = nullptr;	//The capybara that the turn is on
	ListItem<Capybara*>* selectedCapybara = nullptr;	//The capybara wich the action may take effect
	
	GuiButton* attackBtn = nullptr;
	GuiButton* abilityBtn = nullptr;
	GuiButton* inventoryBtn = nullptr;
	GuiButton* runBtn = nullptr;
	List<GuiButton*> menuBtns;

	List<GuiButton*> currentButtons;
	ListItem<GuiButton*>* currentButton = nullptr;

	List<GuiButton*> attackBtns;
	List<GuiText*> enemyInfo;
	List<GuiBar*> enemyBars;

	List<GuiText*> playerNames;
	List<GuiBar*>  playerHealthBars;
	List<GuiBar*>  playerManaBars;
	
	List<GuiText*> playerHeathText;
	List<GuiText*> playerManaText;


	GuiText* currentName = nullptr;

	bool updateInput = true;

	bool showAttackMenu = false;
	bool deleteAttackMenu = false;
	bool showAbilityMenu = false;
	bool createAttackMenu = false;
	bool createTexts = false;
	bool updateCurrentName = false;

	Turn turn = Turn::NONE;
};


#endif // !__BATTLESCENE_H__

