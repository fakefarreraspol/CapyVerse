#include "BattleScene1.h"

BattleScene1::BattleScene1(bool startEnabled) : Module(startEnabled)
{
}
BattleScene1::~BattleScene1()
{
}

bool BattleScene1::Awake(pugi::xml_node&)
{
    return false;
}

bool BattleScene1::Start()
{
    return false;
}

bool BattleScene1::PreUpdate()
{
    return false;
}

bool BattleScene1::Update(float dt)
{
    return false;
}

bool BattleScene1::CleanUp()
{
    return false;
}
