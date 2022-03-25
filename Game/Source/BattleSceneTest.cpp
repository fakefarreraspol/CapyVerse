#define SELECT_OFFSET 0

#include "BattleSceneTest.h"

#include "GuiButton.h"

#include "App.h"
#include "GuiManager.h"
#include "EntityManager.h"

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
	return ret;
}

bool BattleSceneTest::Start()
{
	bool ret = true;

	app->guiManager->Enable();

	enemies.Add(app->entMan->CreateEntity(CapybaraType::TANK, 4, { 1100, 150 }, "Chinabara"));
	enemies.Add(app->entMan->CreateEntity(CapybaraType::TANK, 5, { 1100, 250 }, "Chinabara"));
	enemies.Add(app->entMan->CreateEntity(CapybaraType::TANK, 6, { 1100, 350 }, "Chinabara"));



	attackBtn =	(GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Attack", { 135, 585, 70, 21 }, this);
	abilityBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Ability", { 135, 615, 70, 21 }, this);
	inventoryBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Inventory", { 135, 645, 70, 21 }, this);
	runBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Run", { 135, 675, 70, 21 }, this);


	if (player == nullptr)
		printf("Player is nullptr\n");

	playerTeam = player->GetBattleTeam();

	currentCapybara = playerTeam.start;

	return ret;
}

bool BattleSceneTest::PreUpdate()
{
	bool ret = true;
	
	UpdateInput();

	if (createAttackMenu)
		CreateAttackMenu();

	return ret;
}

bool BattleSceneTest::Update(float dt)
{
	bool ret = true;

	app->guiManager->Draw();

	int posX = currentCapybara->data->GetPosition().x;
	int posY = currentCapybara->data->GetPosition().y + SELECT_OFFSET;
	app->render->DrawCircle(posX, posY, 10, 0, 255, 0);



	return ret;
}

void BattleSceneTest::CreateAttackMenu()
{
	for (int i = 0; i < enemies.Count(); i++)
	{
		GuiButton* enemyBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, i + 4, enemies.At(i)->data->name.GetString(), { 250, i * 30 + 585, 70, 21 }, this);
	}
	createAttackMenu = false;
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
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		if (currentCapybara->prev == nullptr)
			currentCapybara = playerTeam.end;
		else
			currentCapybara = currentCapybara->prev;
	}
}

bool BattleSceneTest::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool BattleSceneTest::CleanUp()
{
	bool ret = true;
	return ret;
}

void BattleSceneTest::SetPlayer(Player* player)
{
	this->player = player;
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
			printf("AttackBtn");
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
		}
		if (control->id == 5)
		{
			currentCapybara->data->Attack(enemies.At(1)->data);
		}
		if (control->id == 6)
		{
			currentCapybara->data->Attack(enemies.At(2)->data);
		}
	}break;

	}
	return ret;
}
