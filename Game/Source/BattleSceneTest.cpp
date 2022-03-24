#define SELECT_OFFSET 20

#include "BattleSceneTest.h"

#include "GuiButton.h"

#include "App.h"
#include "GuiManager.h"

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

	attackBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, "Attack", { 135, 585, 70, 21 }, this);
	abilityBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Ability", { 135, 615, 70, 21 }, this);
	inventoryBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Inventory", { 135, 645, 70, 21 }, this);
	runBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Run", { 135, 675, 70, 21 }, this);


	if (player == nullptr)
		printf("Player is nullptr\n");

	currentCapybara = player->GetBattleTeam().start;

	return ret;
}

bool BattleSceneTest::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool BattleSceneTest::Update(float dt)
{
	bool ret = true;

	UpdateInput();

	app->guiManager->Draw();

	return ret;
}

void BattleSceneTest::ShowAttackMenu()
{
}

void BattleSceneTest::ShowAbilityMenu()
{
}

void BattleSceneTest::UpdateInput()
{
	int posX = currentCapybara->data->GetPosition().x;
	int posY = currentCapybara->data->GetPosition().y + SELECT_OFFSET;
	app->render->DrawCircle(posX, posY, 10, 0, 255, 0);

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		if (currentCapybara->next == nullptr)
		{
			currentCapybara = player->GetBattleTeam().start;
			return;
		}

		currentCapybara = currentCapybara->next;
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
