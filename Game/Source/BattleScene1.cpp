#include "BattleScene1.h"

#include "Enemy.h"

#include "App.h"
#include "BattleManager.h"
#include "EntityManager.h"
#include "Player.h"

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

    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 10, { 10, 10 }, "Enemy");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 720, 150 }, "Chinabara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 720, 250 }, "Rainbowbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 720, 350 }, "Punkibara"));


    return true;
}

bool BattleScene1::Start()
{
    bool ret = true;

    enemy->SetCombat(true);

    app->battleManager->SetEnemy(enemy);

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

    if (app->battleManager->GetTurn() == Turn::ENEMY)
    {
        enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(1)->data);
        app->battleManager->SetTurn(Turn::PLAYER);
    }

    if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
        app->render->camera.y -= 1;

    if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
        app->render->camera.y += 1;

    if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
        app->render->camera.x -= 1;

    if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
        app->render->camera.x += 1;

    return ret;
}

bool BattleScene1::CleanUp()
{
    bool ret = true;
    return ret;
}
