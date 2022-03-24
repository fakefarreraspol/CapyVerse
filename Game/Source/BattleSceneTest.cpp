#include "BattleScene.h"

BattleScene::BattleScene(bool startEnabled) : Module(startEnabled)
{
}

BattleScene::~BattleScene()
{
}

bool BattleScene::Start()
{
	return false;
}

bool BattleScene::PreUpdate()
{
	return false;
}

bool BattleScene::Update(float dt)
{
	return false;
}

bool BattleScene::PostUpdate()
{
	return false;
}

bool BattleScene::CleanUp()
{
	bool ret = true;
	return true;
}
