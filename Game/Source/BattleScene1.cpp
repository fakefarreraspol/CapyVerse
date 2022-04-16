#include "BattleScene1.h"

#include "Enemy.h"
#include "Player.h"

#include "App.h"

#include "BattleManager.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "Scene.h"


BattleScene1::BattleScene1(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene1");
}
BattleScene1::~BattleScene1()
{
}

bool BattleScene1::Awake(pugi::xml_node&)
{
    

    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 10, { 10, 10 }, "Enemy");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 720, 150 }, "Retrobara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 720, 250 }, "Simpbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 720, 350 }, "Egirlbara"));

    app->scene->NPCs.Add(enemy);

    return true;
}

bool BattleScene1::Start()
{
    bool ret = true;
    app->battleManager->SetTurn(Turn::PLAYER);
    enemy->SetCombat(true);

    app->battleManager->SetEnemy(enemy);

    app->battleManager->Enable();

    return ret;
}

bool BattleScene1::PreUpdate()
{
    bool ret = true;
    for (int i = 0; i < enemy->GetBattleTeam().Count(); i++)
    {
       if (enemy->GetBattleTeam().At(i)->data->GetHealth() <= 0)
       {
           enemy->GetBattleTeam().Del(enemy->GetBattleTeam().At(i));
       }
    }
    
    return ret;
}

bool BattleScene1::Update(float dt)
{
    bool ret = true;
    srand(time(NULL));
    randomNum = rand() % 2;
    //if (app->battleManager->GetTurn() == Turn::ENEMY)
    //{
    //    if (enemy->GetBattleTeam().At(1) != nullptr)
    //    {
    //        //TODO: Code the Enemy AI

    //        enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(1)->data);
    //    }
    //    app->battleManager->EndTurn();
    //}

    
    //enemy Turn
    if (app->battleManager->GetTurn() == Turn::ENEMY)
    {
        //supp
        for (int i = 0; i < enemy->GetBattleTeam().Count() && enemy->GetBattleTeam().At(i) != nullptr && enemy->GetBattleTeam().At(1) != nullptr; i++)
        {
            if (enemy->GetBattleTeam().At(i)->data->GetHealth() <= enemy->GetBattleTeam().At(i)->data->GetMaxHealth() / 1.5)
            {
                enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(1)->data->SetAttack(false);
                break;
            }
           
        }
        if (enemy->GetBattleTeam().At(1)->data->CanAttack())
        {
            if (app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data != nullptr)
            {
                enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data);
            }
            else
            {
                if (enemy->GetBattleTeam().At(1)->data->GetHealth() < enemy->GetBattleTeam().At(1)->data->GetMaxHealth() / 7) enemy->GetBattleTeam().At(1)->data->Heal(1);
            }
        }
        else enemy->GetBattleTeam().At(1)->data->Heal(2);

        //tank

        app->battleManager->EndTurn();
    }
    
    if (enemy->GetBattleTeam().Count() == 0 || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
        app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 120);

   
    return ret;
}

bool BattleScene1::CleanUp()
{
    bool ret = true;
    app->battleManager->Disable();

    enemy->SetCombat(false);
    enemy->Disable();

    return ret;
}
