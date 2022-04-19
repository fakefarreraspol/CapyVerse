#include "BattleScene3.h"

#include "Enemy.h"
#include "Player.h"

#include "App.h"

#include "BattleManager.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "Scene.h"


BattleScene3::BattleScene3(bool startEnabled) : Module(startEnabled)
{
    name.Create("battle_scene1");
}
BattleScene3::~BattleScene3()
{
}

bool BattleScene3::Awake(pugi::xml_node&)
{


    enemy = (Enemy*)app->entMan->CreateEntity(EntityType::ENEMY, 10, { 10, 10 }, "Enemy");

    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 11, { 720, 150 }, "Chinabara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::SUPP, 11, { 720, 250 }, "Rainbowbara"));
    enemy->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::DPS, 11, { 720, 350 }, "Punkibara"));

    app->scene->NPCs.Add(enemy);

    return true;
}

bool BattleScene3::Start()
{
    bool ret = true;
    app->battleManager->SetTurn(Turn::PLAYER);
    enemy->SetCombat(true);

    app->battleManager->SetEnemy(enemy);

    app->battleManager->Enable();

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
        if (enemy->GetBattleTeam().At(1)->data != nullptr)
        {
            if (enemy->GetBattleTeam().At(1)->data->GetHealth() <= enemy->GetBattleTeam().At(1)->data->GetMaxHealth() - 7)
            {
                enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(1)->data);
                if (enemy->GetBattleTeam().At(1)->data->UseAbility(enemy->GetBattleTeam().At(1)->data) != false) enemy->GetBattleTeam().At(1)->data->SetAttack(false);
            }
            if (enemy->GetBattleTeam().At(1)->data->CanAttack())
            {

                if (app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data != nullptr)
                {
                    enemy->GetBattleTeam().At(1)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data);
                }
                else if (enemy->GetBattleTeam().At(1)->data->GetHealth() < enemy->GetBattleTeam().At(1)->data->GetMaxHealth() / 7) enemy->GetBattleTeam().At(1)->data->Heal(2);



            }
            else enemy->GetBattleTeam().At(2)->data->RestoreMana(2);
        }
        
        //tank
        if (enemy->GetBattleTeam().At(0)->data != nullptr)
        {
            if (enemy->GetBattleTeam().At(0)->data->GetHealth() < enemy->GetBattleTeam().At(0)->data->GetMaxHealth() - 6)
            {
                enemy->GetBattleTeam().At(0)->data->UseAbility(enemy->GetBattleTeam().At(0)->data);
                if (enemy->GetBattleTeam().At(0)->data->UseAbility(enemy->GetBattleTeam().At(0)->data) != false) enemy->GetBattleTeam().At(0)->data->SetAttack(false);
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
        

        //dmg
        if (enemy->GetBattleTeam().At(2)->data != nullptr)
        {
            if (enemy->GetBattleTeam().At(2)->data->GetHealth() < enemy->GetBattleTeam().At(2)->data->GetMaxHealth() - 8)
            {
                enemy->GetBattleTeam().At(2)->data->UseAbility(enemy->GetBattleTeam().At(2)->data);
                if (enemy->GetBattleTeam().At(2)->data->UseAbility(enemy->GetBattleTeam().At(2)->data) == true) enemy->GetBattleTeam().At(2)->data->SetAttack(false);
            }
            if (enemy->GetBattleTeam().At(2)->data->CanAttack())
            {

                if (app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data != nullptr)
                {
                    enemy->GetBattleTeam().At(2)->data->Attack(app->battleManager->GetPlayer()->GetBattleTeam().At(randomNum)->data);
                }
                else if (enemy->GetBattleTeam().At(2)->data->GetHealth() < enemy->GetBattleTeam().At(2)->data->GetMaxHealth() / 7) enemy->GetBattleTeam().At(2)->data->Heal(2);



            }
            else enemy->GetBattleTeam().At(2)->data->RestoreMana(2);
        }
       

        app->battleManager->EndTurn();
    }

    if (enemy->GetBattleTeam().Count() == 0 || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
        app->fadeToBlack->MFadeToBlack(this, (Module*)app->eobScene, 120);


    return ret;
}

bool BattleScene3::CleanUp()
{
    bool ret = true;
    app->battleManager->Disable();

    enemy->SetCombat(false);
    enemy->Disable();

    return ret;
}