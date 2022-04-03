#define SELECT_OFFSET 0

#include <string.h>

#include "BattleManager.h"

#include "GuiButton.h"

#include "App.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "GuiText.h"
#include "GuiBar.h"

#include "Enemy.h"
#include "Capybara.h"
#include "Player.h"

BattleManager::BattleManager(bool startEnabled) : Module(startEnabled)
{
}

BattleManager::~BattleManager()
{
}

bool BattleManager::Awake(pugi::xml_node&)
{
	bool ret = true;

	

	return ret;
}

bool BattleManager::Start()
{
	bool ret = true;

	app->guiManager->Enable();
	

	attackBtn =	(GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Attack", { 135, 585, 75, 21 }, this);
	abilityBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Ability", { 135, 615, 75, 21 }, this);
	inventoryBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Inventory", { 135, 645, 75, 21 }, this);
	runBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Run", { 135, 675, 75, 21 }, this);
	menuBtns.Add(attackBtn);
	menuBtns.Add(abilityBtn);
	//menuBtns.Add(inventoryBtn);
	menuBtns.Add(runBtn);

	inventoryBtn->state = GuiControlState::DISABLED;


	if (player == nullptr)
	{
		printf("Player is nullptr\n");
		ret = false;
	}

	player->SetCombat(true);

	for (int i = 0; i < player->GetBattleTeam().Count(); i++)
	{
		playerTeam.Add(player->GetBattleTeam().At(i)->data);
	}

	currentCapybara = playerTeam.start;
	currentButtons = menuBtns;
	currentButton = currentButtons.start;


	enemies = enemy->GetBattleTeam();

	CreateTexts();



	return ret;
}

bool BattleManager::PreUpdate()
{
	bool ret = true;
	
	if (createTexts)
		CreateTexts();


	if (deleteAttackMenu)
	{
		for (int i = 0; i < attackBtns.Count(); i++)
		{
			app->guiManager->DestroyGuiControl(attackBtns.At(i)->data);
			app->guiManager->DestroyGuiControl(enemyInfo.At(i)->data);
			app->guiManager->DestroyGuiControl(enemyBars.At(i)->data);
		}
		enemyBars.Clear();
		enemyInfo.Clear();
		attackBtns.Clear();
		currentButtons = menuBtns;
		currentButton = currentButtons.start;

		deleteAttackMenu = false;
	}
	if (createAttackMenu)
		CreateAttackMenu();

	for (int i = 0; i < playerHeathText.Count() && i < playerTeam.Count(); i++)
	{
		SString hp("%i/%iHP", playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
		if (strcmp(playerHeathText.At(i)->data->GetText(), hp.GetString()))
		{
			playerHeathText.At(i)->data->SetText(hp.GetString());
			printf("Updating HP\n");
		}
	}
	for (int i = 0; i < playerManaText.Count() && i < playerTeam.Count(); i++)
	{
		SString mp("%i/%iMP", playerTeam.At(i)->data->GetMana(), playerTeam.At(i)->data->GetMaxMana());
		if (strcmp(playerManaText.At(i)->data->GetText(), mp.GetString()))
		{
			playerManaText.At(i)->data->SetText(mp.GetString());
			printf("Updating Mana \n");
		}
	}

	return ret;
}

bool BattleManager::Update(float dt)
{
	bool ret = true;
	
	if (turn == Turn::PLAYER)
	{
		UpdateInput();
	}

	Draw();


	if (showAttackMenu)
		ShowAttackMenu();

	//Updates the character name changes
	if (updateCurrentName)
	{
		app->guiManager->DestroyGuiControl(currentName);
		currentName = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 10, currentCapybara->data->name.GetString(), { 115, 545, 155, 20 }, this, { 255, 255, 255, 1 });
		updateCurrentName = false;
	}
	//Updating the capybaras info
	UpdateInfo();

	return ret;
}

void BattleManager::Draw()
{
	app->guiManager->Draw();

	int posX = currentCapybara->data->GetPosition().x;
	int posY = currentCapybara->data->GetPosition().y + SELECT_OFFSET;
	app->render->DrawCircle(posX, posY, 10, 0, 255, 0);

	int btnX = currentButton->data->bounds.x;
	int btnY = currentButton->data->bounds.y;
	app->render->DrawCircle(btnX, btnY, 10, 0, 255, 0);
}

void BattleManager::UpdateInfo()
{
	for (int i = 0; i < playerHealthBars.Count(); i++)
	{
		playerHealthBars.At(i)->data->UpdateValues(playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
	}
	for (int i = 0; i < playerManaBars.Count(); i++)
	{
		playerManaBars.At(i)->data->UpdateValues(playerTeam.At(i)->data->GetMana(), playerTeam.At(i)->data->GetMaxMana());
	}
}

void BattleManager::CreateAttackMenu()
{
	for (int i = 0; i < enemies.Count(); i++)
	{
		attackBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 4, enemies.At(i)->data->name.GetString(), { 250, i * 50 + 550, 155, 20 }, this));

		SString enemyHealth("%i/%i HP", enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
		enemyBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::SLIDERBAR, i + 4, "EnemyBar", { 250, i * 50 + 575, 155, 20 }, this));
		enemyInfo.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, i + 4, enemyHealth.GetString(), { 250, i * 50 + 575, 155, 20 }, this,  {255, 255, 255, 1}));
	}
	for (int i = 0; i < enemyBars.Count(); i++)
	{
		enemyBars.At(i)->data->UpdateValues(enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
	}

	createAttackMenu = false;
	currentButton = attackBtns.start;
	currentButtons = attackBtns;

	return;
}

void BattleManager::ShowAttackMenu()
{	
}

void BattleManager::ShowAbilityMenu()
{
}

void BattleManager::UpdateInput()
{

	if (!showAbilityMenu && !showAttackMenu)
	{
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			if (currentCapybara->next == nullptr || !currentCapybara->next->data->CanAttack())
				currentCapybara = playerTeam.start;
			else if (currentCapybara->next->data->CanAttack())
				currentCapybara = currentCapybara->next;

			updateCurrentName = true;
		}
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			if (currentCapybara->prev == nullptr)
				currentCapybara = playerTeam.end;
			else
				currentCapybara = currentCapybara->prev;

			updateCurrentName = true;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		if (currentButton->next == nullptr)
		{
			currentButton->data->state = GuiControlState::NORMAL;
			currentButton = currentButtons.start;
		}
		else
		{
			currentButton->data->state = GuiControlState::NORMAL;
			currentButton = currentButton->next;
		}

	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{	
		if (currentButton->prev == nullptr)
		{
			currentButton->data->state = GuiControlState::NORMAL;
			currentButton = currentButtons.end;
		}
		else
		{
			currentButton->data->state = GuiControlState::NORMAL;
			currentButton = currentButton->prev;
		}
	}
	currentButton->data->state = GuiControlState::FOCUSED;
}

bool BattleManager::PostUpdate()
{
	bool ret = true;

	for (ListItem<Capybara*>* e = enemies.start; e != nullptr; e = e->next)
	{
		if(e->data->GetHealth() <= 0)
		{
			enemies.Del(e);
			createAttackMenu = true;
		}
	}

	return ret;
}

bool BattleManager::CleanUp()
{
	bool ret = true;

	app->guiManager->Disable();

	return ret;
}

void BattleManager::SetPlayer(Player* player)
{
	this->player = player;
}

void BattleManager::SetEnemy(Enemy* enemy)
{
	this->enemy = enemy;
}

void BattleManager::SetTurn(Turn turn)
{
	this->turn = turn;
}

Turn BattleManager::GetTurn()
{
	return this->turn;
}

void BattleManager::CreateTexts()
{
	currentName = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 10, currentCapybara->data->name.GetString(), { 115, 545, 155, 20 }, this, { 255, 255, 255, 1 });

	for (int i = 0; i < playerTeam.Count(); i++)
	{
		//Creating the character name text
		app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, playerTeam.At(i)->data->name.GetString(), {i * 450 + 15, 20, 155, 20}, this, {255, 255, 255, 1});

		//Creating the health bar
		playerHealthBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::SLIDERBAR, 20 + i, "HealthBar", { i * 450 + 15, 60, 155, 20 }, this ));
		//Creating the health text
		SString hp("%i/%iHP", playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
		playerHeathText.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, hp.GetString(), {i * 450 + 15, 60, 155, 20}, this, {255, 255, 255, 1}));

		//Creating the mana bar
		playerManaBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::SLIDERBAR, 20 + i, "ManaBar", { i * 450 + 15, 85, 155, 20 }, this));
		//Creating the mana text
		SString mp("%i/%iMP", playerTeam.At(i)->data->GetMana(), playerTeam.At(i)->data->GetMaxMana());
		playerManaText.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, mp.GetString(), { i * 450 + 15, 85, 155, 20 }, this, { 255, 255, 255, 1 }));
	}
	

	createTexts = false;

	return;
}

bool BattleManager::OnGuiMouseClickEvent(GuiControl* control)
{
	bool ret = true;
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		if (control->id == 0)
		{
			showAttackMenu = !showAttackMenu;
			createAttackMenu = true;

		}
		if (control->id == 1)
		{

		}
		if (control->id == 2)
		{

		}
		if (control->id == 3)
		{
			
		}
		if (control->id == 4)
		{
			currentCapybara->data->Attack(enemies.At(0)->data);
			showAttackMenu = false;
			deleteAttackMenu = true;
			turn = Turn::ENEMY;
		}
		if (control->id == 5)
		{
			currentCapybara->data->Attack(enemies.At(1)->data);
			showAttackMenu = false;
			deleteAttackMenu = true;
			turn = Turn::ENEMY;
		}
		if (control->id == 6)
		{
			currentCapybara->data->Attack(enemies.At(2)->data);
			showAttackMenu = false;
			deleteAttackMenu = true;
			turn = Turn::ENEMY;
		}
	}break;

	}
	return ret;
}
