#include "BattleSceneTest.h"

BattleSceneTest::BattleSceneTest(bool startEnabled) : Module(startEnabled)
{
}

BattleSceneTest::~BattleSceneTest()
{
}

bool BattleSceneTest::Awake(pugi::xml_node&)
{
	return false;
}

bool BattleSceneTest::Start()
{
	return false;
}

bool BattleSceneTest::PreUpdate()
{
	return false;
}

bool BattleSceneTest::Update(float dt)
{
	return false;
}

bool BattleSceneTest::PostUpdate()
{
	return false;
}

bool BattleSceneTest::CleanUp()
{
	bool ret = true;
	return true;
}
