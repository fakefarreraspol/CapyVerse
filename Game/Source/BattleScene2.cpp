#include "BattleScene2.h"

#include "Enemy.h"
#include "Player.h"

#include "App.h"

#include "BattleManager.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "Scene.h"
#include "Audio.h"
#include "EOBScene.h"



BattleScene2::BattleScene2(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene1");
}
BattleScene2::~BattleScene2()
{
}

bool BattleScene2::Awake(pugi::xml_node&)
{


    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 11, { 600, 350 }, "Enemy");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 928, 305 }, "Chadbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 750, 443 }, "Rainbowbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 1115, 444 }, "Emobara"));
    for (int i = 0; i < enemy->GetBattleTeam().Count(); i++)
    {
        enemy->GetBattleTeam().At(i)->data->enemy = true;
        enemy->GetBattleTeam().At(i)->data->SetLevel(10);
    }
    app->scene->NPCs.Add(enemy);
    enemy->Disable();
    return true;
}

bool BattleScene2::Start()
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

bool BattleScene2::PreUpdate()
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

bool BattleScene2::Update(float dt)
{
    bool ret = true;
    srand((uint)time((time_t)0));
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
        if (enemy->GetBattleTeam().At(1) != nullptr)
        {
            if (enemy->GetBattleTeam().At(1)->data->GetHealth() <= enemy->GetBattleTeam().At(1)->data->GetMaxHealth() - 1)
            {
                //enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(1)->data);
                if (enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(1)->data) != false) enemy->GetBattleTeam().At(1)->data->SetAttack(false);

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
            else enemy->GetBattleTeam().At(1)->data->RestoreMana(5);
        }
       

        //tank
        if (enemy->GetBattleTeam().At(0) != nullptr)
        {
            if (enemy->GetBattleTeam().At(0)->data->GetType() == CapybaraType::TANK)
            {
                for (int i = 0; i < app->battleManager->GetPlayer()->GetBattleTeam().Count(); i++)
                {
                    if (app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data != nullptr && enemy->GetBattleTeam().At(i) != nullptr)
                    {
                        if ((app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->GetHealth() <= enemy->GetBattleTeam().At(i)->data->GetMaxHealth() / 3))
                        {
                            //enemy->GetBattleTeam().At(0)->data->UseAbility(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                            if (enemy->GetBattleTeam().At(0)->data->UseAbility(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data) != false)
                            {
                                enemy->GetBattleTeam().At(0)->data->SetAttack(false);
                            }
                            break;
                        }
                    }
                }
                if (enemy->GetBattleTeam().At(0)->data->CanAttack())
                {
                    if (app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data != nullptr)
                    {
                        enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data);
                    }
                    else
                    {
                        if (enemy->GetBattleTeam().At(0)->data->GetHealth() < enemy->GetBattleTeam().At(0)->data->GetMaxHealth() / 7) enemy->GetBattleTeam().At(0)->data->Heal(3);
                    }
                }
                else enemy->GetBattleTeam().At(0)->data->RestoreMana(3);
            }
        }

        //dmg
        if (enemy->GetBattleTeam().At(2) != nullptr)
        {
            if (enemy->GetBattleTeam().At(2)->data->CanAttack())
            {
                if (enemy->GetBattleTeam().At(2)->data->GetHealth() < enemy->GetBattleTeam().At(0)->data->GetMaxHealth() - 8)
                {
                    if (enemy->GetBattleTeam().At(2)->data->UseAbility(enemy->GetBattleTeam().At(2)->data) != false) enemy->GetBattleTeam().At(2)->data->SetAttack(false);
                }
                else if (app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data != nullptr)
                {
                    enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data);
                }
                else if (enemy->GetBattleTeam().At(2)->data->GetHealth() < enemy->GetBattleTeam().At(2)->data->GetMaxHealth() / 7) enemy->GetBattleTeam().At(2)->data->Heal(2);



            }
            else enemy->GetBattleTeam().At(2)->data->RestoreMana(1);
        }
       

        app->battleManager->EndTurn();
    }

    if (enemy->GetBattleTeam().Count() == 0 || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
    {
        app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 120);
    }

    app->render->DrawTexture(background, 0, 0);
    return ret;
}

bool BattleScene2::CleanUp()
{
    bool ret = true;
    app->battleManager->Disable();

    enemy->SetCombat(false);
    enemy->Disable();
    app->eobScene->SetXP(90);
    app->tex->UnLoad(background);
    app->entMan->DestroyEntity(enemy);
   
    return ret;
}