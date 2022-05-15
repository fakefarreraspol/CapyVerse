#include "BattleScene4.h"

#include "Enemy.h"
#include "Player.h"

#include "App.h"

#include "BattleManager.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "Scene.h"
#include "EOBScene.h"
#include "QuestManager.h"
#include "Audio.h"


BattleScene4::BattleScene4(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene4");
}
BattleScene4::~BattleScene4()
{
}

bool BattleScene4::Awake(pugi::xml_node&)
{
    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 10, { 1732, 1220 }, "Mills");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 928, 443 }, "Retrobara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 750, 443 }, "Simpbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 1115, 444 }, "Egirlbara"));
    enemy->Disable();

    enemy->dialog = new Dialog(1);
    DialogNode* fst0 = new DialogNode("You look like an old friend. She stole my capybaras and traded them for capycoins.");
    DialogNode* sec0 = enemy->dialog->AddOption(fst0, "You look like him... I'm not gonna risk it and destroy you here now!", "");
    enemy->dialog->AddFirstNode(fst0);

    for (int i = 0; i < enemy->GetBattleTeam().Count(); i++)
    {
        enemy->GetBattleTeam().At(i)->data->enemy = true;
        enemy->GetBattleTeam().At(i)->data->SetLevel(1);
    }
    app->scene->NPCs.Add(enemy);
    enemy->Disable();
    return true;
}

bool BattleScene4::Start()
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

bool BattleScene4::PreUpdate()
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

bool BattleScene4::Update(float dt)
{
    bool ret = true;
    srand((uint)time((time_t)0));
    randomNum = rand() % 2;
   
    if (app->battleManager->GetTurn() == Turn::ENEMY)
    {
        
       /* for (int i = 0; i < 3; i++)
        {
            if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
            {
                enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                break;
            }
        }*/
        for (int i = 0; i < 3; i++)
        {
            if(enemy->GetBattleTeam().At(i) != nullptr) enemy->GetBattleTeam().At(i)->data->SetAttack(true);
        }
        //tank
        if (enemy->GetBattleTeam().At(0) != nullptr)
        {

            for (int i = 0; i < 3; i++)
            {
                if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
                {
                    if (app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->GetHealth() < 25)
                    {
                        enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                        enemy->GetBattleTeam().At(0)->data->UseAbility(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                        break;
                    }

                }
            }
        }

        //supp
        if (enemy->GetBattleTeam().At(1) != nullptr)
        {
            for (int i = 0; i < 3; i++)
            {
                if (enemy->GetBattleTeam().At(i) != nullptr)
                {
                    if (enemy->GetBattleTeam().At(i)->data->GetMana() <= enemy->GetBattleTeam().At(i)->data->GetMaxMana() / 2)
                    {
                        if (enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(i)->data) == true)
                        {
                            enemy->GetBattleTeam().At(1)->data->SetAttack(false);
                        }

                    }
                }
                

            }
            if (enemy->GetBattleTeam().At(1)->data->CanAttack())
            {
                for (int j = 0; j < 3; j++)
                {
                    if (app->battleManager->GetPlayer()->GetBattleTeam().At(j) != nullptr)
                    {
                        if (app->battleManager->GetPlayer()->GetBattleTeam().At(j)->data->GetHealth() > 0)
                        {
                            enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(j)->data);
                            break;
                        }

                    }
                }
            }
        }



        //damage
        if (enemy->GetBattleTeam().At(2) != nullptr)
        {
            if (enemy->GetBattleTeam().At(2)->data->UseAbility(enemy->GetBattleTeam().At(2)->data) == false)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
                    {
                        if (app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->GetHealth() > 0)
                        {
                            enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                            break;
                        }

                    }
                }
            }
        }
        
        app->battleManager->EndTurn();
    }

    if (enemy->GetBattleTeam().Count() == 0 || (app->GetDebug() && app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN))
    {
        app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 2);
        app->eobScene->playerWin = true;
    }

    for (int i = 0, j = 0; i < app->battleManager->GetPlayer()->GetBattleTeam().Count(); i++)
    {
        if (app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->GetHealth() <= 0)
        {
            app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->SetCombat(false);
            j++;
        }
        if (j == app->battleManager->GetPlayer()->GetBattleTeam().Count())
        {
            app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 2);
            app->eobScene->playerWin = false;
        }
    }

    app->render->DrawTexture(background, 0, 0);
    return ret;
}

bool BattleScene4::CleanUp()
{
    bool ret = true;
    app->battleManager->Disable();
    app->eobScene->SetXP(60);
    enemy->SetCombat(false);
    enemy->Disable();
    app->tex->UnLoad(background);
   
    return ret;
}
