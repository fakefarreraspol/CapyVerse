#define SELECT_OFFSET 0

#include <string.h>

#include "BattleManager.h"

#include "GuiButton.h"

#include "App.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "GuiText.h"
#include "GuiBar.h"
#include "Textures.h"

#include "Enemy.h"
#include "Capybara.h"
#include "Player.h"
#include "Pause.h"
#include "Fonts.h"
#include "Log.h"
#include "Audio.h"

BattleManager::BattleManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("BattleManager");
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
	LOG("Starting battle manager");
	app->guiManager->Enable();
	battlewonSFX = app->audio->LoadFx("Assets/Audio/Fx/battle-won.wav");
	attack01SFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-attack1.wav");
	attack02SFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-attack2.wav");
	attack03SFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-attack3.wav");
	app->pauseMenu->Enable();
	attackBtn =	(GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Attack", { 135, 585, 75, 21 }, this);
	abilityBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Ability", { 135, 615, 75, 21 }, this);
	//inventoryBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Inventory", { 135, 645, 75, 21 }, this);
	//runBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Run", { 135, 675, 75, 21 }, this);
	menuBtns.Add(attackBtn);
	menuBtns.Add(abilityBtn);
	//menuBtns.Add(inventoryBtn);
	//menuBtns.Add(runBtn);

	//inventoryBtn->state = GuiControlState::DISABLED;


	if (player == nullptr)
	{
		printf("Player is nullptr\n");
		ret = false;
	}
	player->Disable();
	player->SetCombat(true);
	player->canMove = false;

	for (uint i = 0; i < player->GetBattleTeam().Count(); i++)
	{
		playerTeam.Add(player->GetBattleTeam().At(i)->data);
	}

	currentCapybara = playerTeam.start;
	currentButtons = menuBtns;
	currentButton = currentButtons.start;


	for (uint i = 0; i < enemy->GetBattleTeam().Count(); i++)
	{
		enemies.Add(enemy->GetBattleTeam().At(i)->data);
	}

	CreateTexts();

	selectedArrow = app->tex->Load("Assets/Menus/selectedarrow.png");
	arrow = app->tex->Load("Assets/Menus/arrow.png");
	capyinfo = app->tex->Load("Assets/Menus/menus.png");

	if (ret) LOG("Succesfully started battle manager");
	else LOG("Error while starting the battle manager");

	return ret;
}

bool BattleManager::PreUpdate()
{
	bool ret = true;

	DeleteAttackMenu();
	DeleteAbilityMenu();
	//Updating the capybaras info
	UpdatePlayerInfo();

	return ret;
}

void BattleManager::DeleteAttackMenu()
{
	if (deleteAttackMenu)
	{
		for (uint i = 0; i < attackBtns.Count(); i++)
		{
			
			app->guiManager->DestroyGuiControl(attackBtns.At(i)->data);
			app->guiManager->DestroyGuiControl(attackInfo.At(i)->data);
			app->guiManager->DestroyGuiControl(attackBars.At(i)->data);
		}
		attackBars.Clear();
		attackInfo.Clear();
		attackBtns.Clear();
		currentButtons = menuBtns;
		currentButton = currentButtons.start;


		deleteAttackMenu = false;
	}
}

void BattleManager::DeleteAbilityMenu()
{
	if (deleteAbilityMenu)
	{
		for (uint i = 0; i < abilityBtns.Count(); i++)
			app->guiManager->DestroyGuiControl(abilityBtns.At(i)->data);

		for (uint i = 0; i < abilityBars.Count(); i++)
			app->guiManager->DestroyGuiControl(abilityBars.At(i)->data);

		for (uint i = 0; i < abilityInfo.Count(); i++)
			app->guiManager->DestroyGuiControl(abilityInfo.At(i)->data);
	
		abilityBars.Clear();
		abilityInfo.Clear();
		abilityBtns.Clear();
		currentButtons = menuBtns;
		currentButton = currentButtons.start;


		deleteAbilityMenu = false;
	}
}



bool BattleManager::Update(float dt)
{
	bool ret = true;
	
	if (turn == Turn::PLAYER && !app->pause)
	{
		UpdateInput();
	}

	Draw();
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (!currentCapybara->data->GetCombat() && currentCapybara->next)
	{
		currentCapybara = currentCapybara->next;
	}
	return ret;
}

void BattleManager::UpdateCurrentName()
{
	currentName->SetText(currentCapybara->data->idName.GetString());
}

void BattleManager::Draw()
{
	//app->guiManager->Draw();

	uint posX = currentCapybara->data->GetPosition().x;
	uint posY = currentCapybara->data->GetPosition().y - 64;
	app->render->DrawTexture(selectedArrow, posX, posY);


	SDL_Rect info{ 0, 255, 270, 122 };
	SDL_Rect options{ 270, 255, 185, 155 };
	SDL_Rect enemy{ 821, 257, 234, 177 };
	app->render->DrawTexture(capyinfo, 0, 0, &info);
	app->render->DrawTexture(capyinfo, 440, 0, &info);
	app->render->DrawTexture(capyinfo, 890, 0, &info);
	app->render->DrawTexture(capyinfo, 75, 530, &options);
	if(showMenu)
		app->render->DrawTexture(capyinfo, 340, 530, &enemy);
}

void BattleManager::UpdatePlayerInfo()
{
	for (uint i = 0; i < playerHealthBars.Count(); i++)
	{
		playerHealthBars.At(i)->data->UpdateValues(playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
	}
	for (uint i = 0; i < playerManaBars.Count(); i++)
	{
		playerManaBars.At(i)->data->UpdateValues(playerTeam.At(i)->data->GetMana(), playerTeam.At(i)->data->GetMaxMana());
	}
	for (uint i = 0; i < playerHeathText.Count() && i < playerTeam.Count(); i++)
	{
		SString hp("%i/%iHP", playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
		if (strcmp(playerHeathText.At(i)->data->GetText(), hp.GetString()))
		{
			playerHeathText.At(i)->data->SetText(hp.GetString());
			printf("Updating HP\n");
		}
	}
	for (uint i = 0; i < playerManaText.Count() && i < playerTeam.Count(); i++)
	{
		SString mp("%i/%iMP", playerTeam.At(i)->data->GetMana(), playerTeam.At(i)->data->GetMaxMana());
		if (strcmp(playerManaText.At(i)->data->GetText(), mp.GetString()))
		{
			playerManaText.At(i)->data->SetText(mp.GetString());
			printf("Updating Mana \n");
		}
	}
	for (uint i = 0; i < playerLevels.Count() && i < playerTeam.Count(); i++)
	{
		SString mp("LVL: %i", playerTeam.At(i)->data->GetLVL());
		if (strcmp(playerLevels.At(i)->data->GetText(), mp.GetString()))
		{
			playerLevels.At(i)->data->SetText(mp.GetString());
			printf("Updating Level \n");
		}
	}
	for (uint i = 0; i < playerStatus.Count() && i < playerTeam.Count(); i++)
	{
		SString status;
		switch (playerTeam.At(i)->data->GetStatus())
		{
		case CapybaraStatus::NONE: status.Create("");				break;
		case CapybaraStatus::BLEED: status.Create("Bleed");			break;
		case CapybaraStatus::BLOATED: status.Create("Bloated");		break;
		case CapybaraStatus::DEFENSIVE: status.Create("Defensive");	break;
		case CapybaraStatus::POISONED: status.Create("Poisoned");	break;
		case CapybaraStatus::RAGE: status.Create("Rage");			break;
		case CapybaraStatus::SLEEP: status.Create("Sleep");			break;
		case CapybaraStatus::STUNED: status.Create("Stuned");		break;
		case CapybaraStatus::TAUNTED: status.Create("Taunted");		break;
		}

		if (strcmp(playerStatus.At(i)->data->GetText(), status.GetString()))
		{
			playerStatus.At(i)->data->SetText(status.GetString());
			printf("Updating Status\n");
		}
	}
}

void BattleManager::CreateAttackMenu()
{
	if (enemies.Count() > 0)
	{
		for (int i = 0; i < enemies.Count(); i++)
		{
			attackBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 4, enemies.At(i)->data->idName.GetString(), { 350, i * 50 + 550, 112, 20 }, this));

			SString enemyHealth("%i/%i HP", enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
			attackBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, i + 4, "EnemyBar", { 350, i * 50 + 575, 112, 9 }, this));
			attackBars.At(i)->data->type = BarType::HEALTH;
			attackInfo.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, i + 4, enemyHealth.GetString(), { 465, i * 50 + 570, 112, 20 }, this, { 255, 255, 255, 1 }, app->fonts->indicatorsFont));
		}
		for (int i = 0; i < attackBars.Count(); i++)
		{
			attackBars.At(i)->data->UpdateValues(enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
		}
		currentButtons = attackBtns;
		currentButton = attackBtns.start;
	}
	return;
}

void BattleManager::CreateAbilityMenu()
{
	
	switch (currentCapybara->data->GetTarget())	
	{
	case CapybaraTarget::ALLIES :
	{
		
		if (playerTeam.Count() > 0)
		{
			for (int i = 0; i < playerTeam.Count(); i++)
			{
				if ((playerTeam.At(i)->data->GetHealth() > 0) && (playerTeam.At(i)!=nullptr))
				{
					abilityBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 7, playerTeam.At(i)->data->idName.GetString(), { 350, i * 50 + 550, 112, 20 }, this));

					SString allyHealth("%i/%i HP", playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
					abilityBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, i + 7, "AllyBar", { 350, i * 50 + 570, 112, 9 }, this));
					if (abilityBars.At(i)!=nullptr) abilityBars.At(i)->data->type = BarType::HEALTH;
					abilityInfo.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, i + 7, allyHealth.GetString(), { 465, i * 50 + 570, 155, 20 }, this, { 255, 255, 255, 1 }, app->fonts->indicatorsFont));
				}
			}
			for (uint i = 0; i < abilityBars.Count(); i++)
			{
				abilityBars.At(i)->data->UpdateValues(playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
			}
	
			currentButton = abilityBtns.start;
			currentButtons = abilityBtns;
			targets = playerTeam;
		}
	}break;
	case CapybaraTarget::ENEMIES:
	{
		if (playerTeam.Count() > 0)
		{
			for (int i = 0; i < enemies.Count(); i++)
			{
				if (enemies.At(i)->data->GetHealth() > 0)
				{
					abilityBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 7, enemies.At(i)->data->idName.GetString(), { 350, i * 50 + 550, 112, 20 }, this));

					SString allyHealth("%i/%i HP", enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
					abilityBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, i + 7, "AllyBar", { 350, i * 50 + 575, 112, 9 }, this));
					abilityInfo.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, i + 7, allyHealth.GetString(), { 465, i * 50 + 570, 112, 9 }, this, { 255, 255, 255, 1 }, app->fonts->indicatorsFont));
					abilityBars.At(i)->data->type = BarType::HEALTH;
				}
			}
			for (uint i = 0; i < abilityBars.Count(); i++)
			{
				abilityBars.At(i)->data->UpdateValues(enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
			}
		
			currentButton = abilityBtns.start;
			currentButtons = abilityBtns;
			targets = enemies;
		}
	}break;

	case CapybaraTarget::HIMSELF:
	{
		abilityBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, currentCapybara->data->idName.GetString(), { 360, 50 + 550, 112, 20 }, this));
		currentButton = abilityBtns.start;
		currentButtons = abilityBtns;
	}break;
	default:
		break;
	}
}

void BattleManager::UpdateInput()
{
	GamePad& pad = app->input->pads[0];

	
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down)
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

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up)
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
			break;
		}
	}
	for (ListItem<Capybara*>* e = playerTeam.start; e != nullptr; e = e->next)
	{
		if (e->data->GetHealth() <= 0)
		{
			e->data->SetAttack(false);
		}
	}
	return ret;
}

bool BattleManager::CleanUp()
{
	bool ret = true;
	app->guiManager->Disable();

	app->tex->UnLoad(arrow);

	enemies.Clear();
	playerTeam.Clear();
	


	playerNames.Clear();
	playerHealthBars.Clear();
	playerManaBars.Clear();
	playerLevels.Clear();
	playerStatus.Clear();
	
	playerHeathText.Clear();
	playerManaText.Clear();
	
	/*if (menuBtns.Count() > 0)
	{
		for (ListItem<GuiButton*>* b = currentButtons.start; b != nullptr; b = b->next)
		{
			menuBtns.Del(b);
		}
	}*/

	menuBtns.Clear();
	app->tex->UnLoad(capyinfo);
	app->pauseMenu->Disable();
	return ret;
}

void BattleManager::SetPlayer(Player* player)
{
	this->player = player;
}

Player* BattleManager::GetPlayer()
{
	return this->player;
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

void BattleManager::EndTurn()
{
	if (turn == Turn::PLAYER)
		turn = Turn::ENEMY;
	else if (turn == Turn::ENEMY)
	{
		turn = Turn::PLAYER;
		if (playerTeam.start->data->GetCombat())
		{
			currentCapybara = playerTeam.start;
		}
		else if (playerTeam.start->next->data->GetCombat())
		{
			currentCapybara = playerTeam.start->next;
		}
		else if (playerTeam.start->next->next->data->GetCombat())
		{
			currentCapybara = playerTeam.start->next->next;
		}
	}
	

	for (uint i = 0; i < playerTeam.Count(); i++)
	{
		playerTeam.At(i)->data->UpdateStatus();
	}
	for (uint i = 0; i < enemies.Count(); i++)
	{
		enemies.At(i)->data->UpdateStatus();
	}
}

void BattleManager::CreateTexts()
{
	currentName = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 10, currentCapybara->data->idName.GetString(), { 115, 545, 155, 20 }, this, { 255, 255, 255, 1 });

	for (int i = 0; i < playerTeam.Count(); i++)
	{
		//Creating the character name text
		app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, playerTeam.At(i)->data->idName.GetString(), {i * 450 + 15, 40, 155, 20}, this, {255, 255, 255, 1});

		//Creating the character LVL text
		SString lvl("LVL: %i", playerTeam.At(i)->data->GetLVL());
		playerLevels.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, lvl.GetString(), {i * 450 + 150, 40, 155, 20}, this, {255,255,255,1}, app->fonts->indicatorsFont));

		//Creating the health bar
		playerHealthBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, 20 + i, "HealthBar", { i * 450 + 15, 60, 112, 9 }, this ));
		playerHealthBars.At(i)->data->type = BarType::HEALTH;
		//Creating the health text
		SString hp("%i/%iHP", playerTeam.At(i)->data->GetHealth(), playerTeam.At(i)->data->GetMaxHealth());
		playerHeathText.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, hp.GetString(), {i * 450 + 128, 60, 155, 20}, this, {255, 255, 255, 1}, app->fonts->indicatorsFont));

		//Creating the mana bar
		playerManaBars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, 20 + i, "ManaBar", { i * 450 + 15, 85, 112, 12 }, this));
		playerManaBars.At(i)->data->type = BarType::MANA;
		//Creating the mana text
		SString mp("%i/%iMP", playerTeam.At(i)->data->GetMana(), playerTeam.At(i)->data->GetMaxMana());
		playerManaText.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, mp.GetString(), { i * 450 + 128, 85, 155, 20 }, this, { 255, 255, 255, 1 }, app->fonts->indicatorsFont));
		
		//Creating the status text
		SString status;
		switch (playerTeam.At(i)->data->GetStatus())
		{
		case CapybaraStatus::NONE: status.Create("");				break;
		case CapybaraStatus::BLEED: status.Create("Bleed");			break;
		case CapybaraStatus::BLOATED: status.Create("Bloated");		break;
		case CapybaraStatus::DEFENSIVE: status.Create("Defensive");	break;
		case CapybaraStatus::POISONED: status.Create("Poisoned");	break;
		case CapybaraStatus::RAGE: status.Create("Rage");			break;
		case CapybaraStatus::SLEEP: status.Create("Sleep");			break;
		case CapybaraStatus::STUNED: status.Create("Stuned");		break;
		case CapybaraStatus::TAUNTED: status.Create("Taunted");		break;
		}
		playerStatus.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, status.GetString(), { i * 450 + 200, 15, 155, 20 }, this, { 255, 255, 255, 1 }, app->fonts->indicatorsFont));
	}
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
			CreateAttackMenu();
			showMenu = true;
		}
		if (control->id == 1)
		{
			CreateAbilityMenu();
			showMenu = true;
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
			app->audio->PlayFx(app->battleManager->attack01SFX);
			
		}
		if (control->id == 5)
		{
			currentCapybara->data->Attack(enemies.At(1)->data);
			app->audio->PlayFx(app->battleManager->attack02SFX);
		
		}
		if (control->id == 6)
		{
			currentCapybara->data->Attack(enemies.At(2)->data);
			app->audio->PlayFx(app->battleManager->attack03SFX);
		
		}
		//Attack
		if (control->id >= 4 && control->id <= 6)
		{
			deleteAttackMenu = true;
			
			if (currentCapybara->next == nullptr)
			{
				EndTurn();
			}
			else
			{
				if(currentCapybara->next->data->GetCombat())
				{
					currentCapybara = currentCapybara->next;
				}
				else
				{
					if (currentCapybara->next->next)
					{
						if(currentCapybara->next->next->data->GetCombat())
							currentCapybara = currentCapybara->next->next;
					}
					else
					{
						EndTurn();
					}
				}
			}
			UpdateCurrentName();
			showMenu = false;
		}
		if (control->id == 7)
		{
			currentCapybara->data->UseAbility(targets.At(0)->data);
		}
		if (control->id == 8)
		{
			currentCapybara->data->UseAbility(targets.At(1)->data);
		}
		if (control->id == 9)
		{
			currentCapybara->data->UseAbility(targets.At(2)->data);
		}
		if (control->id == 10)
		{
			currentCapybara->data->UseAbility(currentCapybara->data);
		}
		//Ability
		if (control->id >= 7 && control->id <= 10)
		{
			deleteAbilityMenu = true;
			if (currentCapybara->next == nullptr)
			{
				EndTurn();
			}
			else
			{
				if (currentCapybara->next->data->GetCombat())
				{
					currentCapybara = currentCapybara->next;
				}
				else
				{
					if (currentCapybara->next->next)
					{
						if (currentCapybara->next->next->data->GetCombat())
							currentCapybara = currentCapybara->next->next;
					}
					else
					{
						EndTurn();
					}
				}
			}
			UpdateCurrentName();
			showMenu = false;

		}

	}break;

	}
	return ret;
}
