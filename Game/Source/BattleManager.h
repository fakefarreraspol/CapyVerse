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

	bool PostUpdate();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool CleanUp();
	
	void SetPlayer(Player* player);
	Player* GetPlayer();
	void SetEnemy(Enemy* enemy);
	void SetTurn(Turn turn);
	Turn GetTurn();

private:

	void UpdateCurrentName();
	void Draw();
	void UpdatePlayerInfo();
	void DeleteAttackMenu();
	void DeleteAbilityMenu();
	void CreateAttackMenu();
	void CreateAbilityMenu();
	void UpdateInput();
	void CreateTexts();

private:
	List<Capybara*> enemies;
	List<Capybara*> playerTeam;
	List<Capybara*> targets;

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

	List<GuiButton*> abilityBtns;
	List<GuiText*> abilityInfo;
	List<GuiBar*> abilityBars;

	List<GuiButton*> attackBtns;
	List<GuiText*> attackInfo;
	List<GuiBar*> attackBars;

	//Player info UI
	List<GuiText*> playerNames;
	List<GuiBar*>  playerHealthBars;
	List<GuiBar*>  playerManaBars;
	List<GuiText*> playerLevels;
	List<GuiText*> playerStatus;

	List<GuiText*> playerHeathText;
	List<GuiText*> playerManaText;


	GuiText* currentName = nullptr;

	bool updateInput = true;

	bool deleteAttackMenu = false;
	bool deleteAbilityMenu = false;
	
	Turn turn = Turn::NONE;
};


#endif // !__BATTLESCENE_H__

