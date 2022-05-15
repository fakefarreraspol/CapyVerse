#include "BattleScene3.h"

#include "Enemy.h"
#include "Player.h"

#include "App.h"

#include "BattleManager.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "Scene.h"
#include "Audio.h"
#include "EOBScene.h"
#include "QuestManager.h"

BattleScene3::BattleScene3(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene3");
}
BattleScene3::~BattleScene3()
{
}

bool BattleScene3::Awake(pugi::xml_node&)
{

    SFXchirp = app->audio->LoadFx("Assets/Audio/Fx/capybara-chirp.wav");
    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 12, { 400, 300 }, "Erin");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 928, 443 }, "Chinabara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 750, 443 }, "Pinkbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 1115, 444 }, "Punkibara"));
    enemy->dialog = new Dialog(1);
    DialogNode* fst0 = new DialogNode("Why aRe You Looking at me?");
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

bool BattleScene3::Start()
{
    bool ret = true;
    app->battleManager->SetTurn(Turn::PLAYER);
    background = app->tex->Load("Assets/Textures/Sprites/battleback.png");
    enemy->SetCombat(true);

    app->battleManager->SetEnemy(enemy);

    app->battleManager->Enable();
    app->audio->ChangeMusic(4);
    return ret;
}

bool BattleScene3::PreUpdate()
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

bool BattleScene3::Update(float dt)
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

        //tank
        if (enemy->GetBattleTeam().At(0) != nullptr)
        {
            for (int i = 0; i < 3; i++)
            {

                if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
                {
                    if (enemy->GetBattleTeam().At(0)->data->UseAbility(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data) == false)
                    {
                        if (app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->GetHealth() > 0)
                        {
                            enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                            break;
                        }
                    }


                }
            }
        }
        //supp
        if (enemy->GetBattleTeam().At(1) != nullptr)
        {
            if (enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(1)->data) == false)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
                    {
                        if (app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data->GetHealth() > 0)
                        {
                            enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
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

        /*for (int i = 0; i < 3; i++)
        {
            if (app->battleManager->GetPlayer()->GetBattleTeam().At(i) != nullptr)
            {
                enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                enemy->GetBattleTeam().At(0)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(i)->data);
                break;
            }
        }*/
        app->audio->PlayFx(SFXchirp);
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

bool BattleScene3::CleanUp()
{
    bool ret = true;
    app->battleManager->Disable();
    app->tex->UnLoad(background);
    enemy->SetCombat(false);
    enemy->Disable();
    app->eobScene->SetXP(150);
    
    return ret;
}