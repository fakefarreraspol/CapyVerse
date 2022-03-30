#include "BattleScene1.h"

#include "App.h"
#include "BattleManager.h"

BattleScene1::BattleScene1(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene1");
}
BattleScene1::~BattleScene1()
{
}

bool BattleScene1::Awake(pugi::xml_node&)
{
    app->battleManager->SetTurn(Turn::PLAYER);

    return true;
}

bool BattleScene1::Start()
{
    bool ret = true;

    app->battleManager->Enable();

    return ret;
}

bool BattleScene1::PreUpdate()
{
    bool ret = true;
    return ret;
}

bool BattleScene1::Update(float dt)
{
    bool ret = true;
    return ret;
}

bool BattleScene1::CleanUp()
{
    bool ret = true;
    return ret;
}
