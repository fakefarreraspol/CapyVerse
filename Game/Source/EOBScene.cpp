#include "EOBScene.h"

#include "App.h"

#include "Input.h"
#include "FadeToBlack.h"
#include "BattleManager.h"
#include "GuiManager.h"
#include "Textures.h"

#include "Player.h"
#include "Audio.h"
#include "QuestManager.h"
#include "Fonts.h"



EOBScene::EOBScene(bool startEnabled) : Module(startEnabled)
{
	name.Create("eob_scene");
}

EOBScene::~EOBScene()
{
}

bool EOBScene::Awake(pugi::xml_node&)
{
	bool ret = true;
	return ret;
}

bool EOBScene::Start()
{
	bool ret = true;
	app->guiManager->Enable();
	app->questManager->Enable();

	player = app->battleManager->GetPlayer();
	for (int i = 0; i < player->GetBattleTeam().Count(); i++)
	{
		bars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, 40 + i, "XP", { player->GetBattleTeam().At(i)->data->GetPosition().x - 30,player->GetBattleTeam().At(i)->data->GetPosition().y - 30, 112, 9}, this));
		bars.At(i)->data->type = BarType::XP;
		
		SString xp("%i/%iXP", player->GetBattleTeam().At(i)->data->GetXP(), player->GetBattleTeam().At(i)->data->GetNextXP());
		texts.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40 + i, xp.GetString(), { player->GetBattleTeam().At(i)->data->GetPosition().x + 85,player->GetBattleTeam().At(i)->data->GetPosition().y - 33, 155, 20 }, this, { 255, 255, 255, 255 }, app->fonts->indicatorsFont));
		
		SString lvl("%i LVL", player->GetBattleTeam().At(i)->data->GetLVL());
		lvls.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40 + i, lvl.GetString(), { player->GetBattleTeam().At(i)->data->GetPosition().x,player->GetBattleTeam().At(i)->data->GetPosition().y - 70, 155, 20 }, this, { 255, 255, 255, 255 }));
		lvlUp.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40 + i, "Level Up!", { player->GetBattleTeam().At(i)->data->GetPosition().x + 70,player->GetBattleTeam().At(i)->data->GetPosition().y - 70, 155, 20 }, this, { 255, 255, 255, 255 }, 0, true));
		
		bars.At(i)->data->state = GuiControlState::DISABLED;
		texts.At(i)->data->state = GuiControlState::DISABLED;
		lvls.At(i)->data->state = GuiControlState::DISABLED;
		lvlUp.At(i)->data->state = GuiControlState::DISABLED;
		player->GetBattleTeam().At(i)->data->SetCombat(false);
	}
	win = app->tex->Load("Assets/Menus/victory.png");
	lose = app->tex->Load("Assets/Menus/defeat.png");
	background = app->tex->Load("Assets/Textures/Sprites/battleback.png");
	app->audio->PlayFx(app->battleManager->battlewonSFX);

	if (!app->questManager->IsCompleated(1) && playerWin)
	{
		app->questManager->UpdateQuest(1);
	}
	counter = 200;
	return ret;
}

bool EOBScene::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool EOBScene::Update(float dt)
{
	bool ret = true;
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	
	if (XP >= 0 && counter <= 0)
	{

		for (int i = 0; i < player->GetBattleTeam().Count(); i++)
		{
			bars.At(i)->data->state = GuiControlState::NORMAL;
			texts.At(i)->data->state = GuiControlState::NORMAL;
			lvls.At(i)->data->state = GuiControlState::NORMAL;
			if (player->GetBattleTeam().At(i)->data->GetHealth() < 0)
				player->GetBattleTeam().At(i)->data->AddXp(1);
			else
				player->GetBattleTeam().At(i)->data->AddXp(2);


			player->GetBattleTeam().At(i)->data->SetCombat(true);
			bars.At(i)->data->UpdateValues(player->GetBattleTeam().At(i)->data->GetXP(), player->GetBattleTeam().At(i)->data->GetNextXP());
			SString xp("%i/%iXP", player->GetBattleTeam().At(i)->data->GetXP(), player->GetBattleTeam().At(i)->data->GetNextXP());
			if (strcmp(texts.At(i)->data->GetText(), xp.GetString()))
				texts.At(i)->data->SetText(xp.GetString());

			SString lvl("%i LVL", player->GetBattleTeam().At(i)->data->GetLVL());
			if (strcmp(lvls.At(i)->data->GetText(), lvl.GetString()))
			{
				lvls.At(i)->data->SetText(lvl.GetString());
				lvlUp.At(i)->data->state = GuiControlState::NORMAL;
			}

		}
		XP--;
	}

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->scene, 2);
	}
	app->render->DrawTexture(background, 0, 0);
	if (counter > 0)
	{
		if (playerWin)
			app->render->DrawTexture(win, 0, 0);
		else
			app->render->DrawTexture(lose, 0, 0);
		counter--;
	}

	

	return ret;
}

void EOBScene::SetXP(int xp)
{
	XP = xp;
}

bool EOBScene::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool EOBScene::CleanUp()
{
	bool ret = true;
	app->guiManager->Disable();
	app->questManager->Disable();
	app->tex->UnLoad(win);
	app->tex->UnLoad(lose);
	lvls.Clear();
	texts.Clear();
	bars.Clear();


	return ret;
}
