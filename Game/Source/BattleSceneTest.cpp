#define SELECT_OFFSET 0

#include "BattleSceneTest.h"

#include "GuiButton.h"

#include "App.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "GuiText.h"


#include "Capybara.h"
#include "Player.h"

BattleSceneTest::BattleSceneTest(bool startEnabled) : Module(startEnabled)
{
}

BattleSceneTest::~BattleSceneTest()
{
}

bool BattleSceneTest::Awake(pugi::xml_node&)
{
	bool ret = true;

	enemies.Add(app->entMan->CreateEntity(CapybaraType::TANK, 4, { 1100, 150 }, "Chinabara"));
	enemies.Add(app->entMan->CreateEntity(CapybaraType::TANK, 5, { 1100, 250 }, "Rainbowbara"));
	enemies.Add(app->entMan->CreateEntity(CapybaraType::TANK, 6, { 1100, 350 }, "Punkibara"));

	return ret;
}

bool BattleSceneTest::Start()
{
	bool ret = true;

	app->guiManager->Enable();
	

	attackBtn =	(GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Attack", { 135, 585, 75, 21 }, this);
	abilityBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Ability", { 135, 615, 75, 21 }, this);
	inventoryBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Inventory", { 135, 645, 75, 21 }, this);
	runBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Run", { 135, 675, 75, 21 }, this);


	if (player == nullptr)
	{
		printf("Player is nullptr\n");
		ret = false;
	}
	for (int i = 0; i < player->GetBattleTeam().Count(); i++)
	{
		playerTeam.Add(player->GetBattleTeam().At(i)->data);
	}

	currentCapybara = playerTeam.start;

	CreateTexts();

	currentName = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 10, currentCapybara->data->name.GetString(), { 115, 545, 155, 20 }, this, {0, 0, 0, 0}, {255, 255, 255, 1});

	return ret;
}

bool BattleSceneTest::PreUpdate()
{
	bool ret = true;
	
	if (createTexts)
		CreateTexts();

	if (createAttackMenu)
		CreateAttackMenu();

	if (!showAttackMenu)
	{
		for (int i = 0; i < attackBtns.Count(); i++)
		{
			app->guiManager->DestroyGuiControl(attackBtns.At(i)->data);
			app->guiManager->DestroyGuiControl(enemyInfo.At(i)->data);
		}
	}

	return ret;
}

bool BattleSceneTest::Update(float dt)
{
	bool ret = true;

	UpdateInput();

	app->guiManager->Draw();

	int posX = currentCapybara->data->GetPosition().x;
	int posY = currentCapybara->data->GetPosition().y + SELECT_OFFSET;
	app->render->DrawCircle(posX, posY, 10, 0, 255, 0);

	if (showAttackMenu)
		ShowAttackMenu();

	if (updateCurrentName)
	{
		app->guiManager->DestroyGuiControl(currentName);
		currentName = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 10, currentCapybara->data->name.GetString(), { 115, 545, 155, 20 }, this, { 0, 0, 0, 0 }, { 255, 255, 255, 1 });
		updateCurrentName = false;
	}

	return ret;
}

void BattleSceneTest::CreateAttackMenu()
{
	for (int i = 0; i < enemies.Count(); i++)
	{
		attackBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 4, enemies.At(i)->data->name.GetString(), { 250, i * 50 + 550, 155, 20 }, this));
		SString enemyHealth("%i/%i HP", enemies.At(i)->data->GetHealth(), enemies.At(i)->data->GetMaxHealth());
		enemyInfo.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, i + 4, enemyHealth.GetString(), { 250, i * 50 + 575, 155, 20 }, this, {0, 0, 0, 0}, {255, 255, 255, 1}));
	}
	createAttackMenu = false;

	return;
}

void BattleSceneTest::ShowAttackMenu()
{
}

void BattleSceneTest::ShowAbilityMenu()
{
}

void BattleSceneTest::UpdateInput()
{

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		if (currentCapybara->next == nullptr)
			currentCapybara = playerTeam.start;
		else
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

bool BattleSceneTest::PostUpdate()
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

bool BattleSceneTest::CleanUp()
{
	bool ret = true;

	app->guiManager->Disable();

	return ret;
}

void BattleSceneTest::SetPlayer(Player* player)
{
	this->player = player;
}

void BattleSceneTest::CreateTexts()
{

	for (int i = 0; i < playerTeam.Count(); i++)
	{
		app->guiManager->CreateGuiControl(GuiControlType::TEXT, 20 + i, playerTeam.At(i)->data->name.GetString(), {i * 450 + 15, 60, 155, 20}, this, {0, 0, 0, 0}, {255, 255, 255, 1});
	}

	createTexts = false;

	return;
}

bool BattleSceneTest::OnGuiMouseClickEvent(GuiControl* control)
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
		}
		if (control->id == 5)
		{
			currentCapybara->data->Attack(enemies.At(1)->data);
			showAttackMenu = false;
		}
		if (control->id == 6)
		{
			currentCapybara->data->Attack(enemies.At(2)->data);
			showAttackMenu = false;
		}
	}break;

	}
	return ret;
}
