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


    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 11, { 450, 350 }, "Enemy");

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