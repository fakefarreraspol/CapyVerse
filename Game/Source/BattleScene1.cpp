#include "BattleScene1.h"

#include "Enemy.h"
#include "Player.h"

#include "App.h"

#include "BattleManager.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "Scene.h"
#include "EOBScene.h"
#include "Audio.h"


BattleScene1::BattleScene1(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene1");
}
BattleScene1::~BattleScene1()
{
}

bool BattleScene1::Awake(pugi::xml_node&)
{
    

    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 10, { 400, 400 }, "Enemy");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 928, 305 }, "Retrobara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 750, 443 }, "Simpbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 1115, 444 }, "Egirlbara"));
    enemy->Disable();
    for (int i = 0; i < enemy->GetBattleTeam().Count(); i++)
    {
        enemy->GetBattleTeam().At(i)->data->enemy = true;
        enemy->GetBattleTeam().At(i)->data->SetLevel(4);
    }
    app->scene->NPCs.Add(enemy);
    enemy->Disable();
    return true;
}

bool BattleScene1::Start()
{
    bool ret = true;
    app->battleManager->SetTurn(Turn::PLAYER);
    background = app->tex->Load("Assets/Textures/Sprites/battleback.png");
    enemy->SetCombat(true);

    app->battleManager->SetEnemy(enemy);

    app->battleManager->Enable();

    app->audio->ChangeMusic(3);

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
    for (int i = 0; i < 3; i++)
    {
        if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
        {
            enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
            enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
            enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
            break;
        }
    }

    //enemy Turn
    if (app->battleManager->GetTurn() == Turn::ENEMY)
    {

        ////tank
        //if (enemy->GetBattleTeam().At(0) != nullptr)
        //{
        //    for (int j = 0; j < 3; j++)
        //    {

        //        if (enemy->GetBattleTeam().At(j) != nullptr)
        //        {
        //            if (enemy->GetBattleTeam().At(j)->data->GetHealth() <= enemy->GetBattleTeam().At(j)->data->GetMaxHealth())
        //            {
        //                if (enemy->GetBattleTeam().At(0)->data->UseAbility(enemy->GetBattleTeam().At(j)->data) == false)
        //                {
        //                    for (int i = 0; i < 3; i++)
        //                    {
        //                        if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
        //                        {
        //                            enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
        //                            enemy->GetBattleTeam().At(0)->data->SetAttack(false);
        //                            break;
        //                        }
        //                    }
        //                    enemy->GetBattleTeam().At(0)->data->SetAttack(false);
        //                    break;
        //                }

        //            }

        //        }
        //    }
        //    if (enemy->GetBattleTeam().At(0)->data->CanAttack())
        //    {
        //        for (int i = 0; i < 3; i++)
        //        {
        //            if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
        //            {
        //                enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
        //                enemy->GetBattleTeam().At(0)->data->SetAttack(false);
        //                break;
        //            }
        //        }

        //    }
        //}
        ////supp
        //if (enemy->GetBattleTeam().At(1) != nullptr)
        //{
        //    if (enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(1)->data) == false)
        //    {
        //        for (int i = 0; i < 3; i++)
        //        {
        //            if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
        //            {
        //                enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
        //                break;
        //            }
        //        }
        //    }
        //}
        ////damage
        //if (enemy->GetBattleTeam().At(2) != nullptr)
        //{
        //    if (enemy->GetBattleTeam().At(2)->data->UseAbility(enemy->GetBattleTeam().At(2)->data) == false)
        //    {
        //        for (int i = 0; i < 3; i++)
        //        {
        //            if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
        //            {
        //                enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
        //                break;
        //            }
        //        }
        //    }
        //}
        
        
        for (int i = 0; i < 3; i++)
        {
            if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
            {
                enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                break;
            }
        }
        
        
        app->battleManager->EndTurn();
            
         
        
        

        if (enemy->GetBattleTeam().Count() == 0)
        {
            app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 120);

        }
        if (app->GetDebug() && app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
        {
            app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 120);

        }
        app->render->DrawTexture(background, 0, 0);
        return ret;

    }
}

bool BattleScene1::CleanUp()
{
    bool ret = true;
    app->battleManager->Disable();
    app->eobScene->SetXP(60);
    app->entMan->DestroyEntity(enemy);
    enemy->SetCombat(false);
    enemy->Disable();
    app->tex->UnLoad(background);
   
    return ret;
}
