#include "EOBScene.h"

#include "App.h"

#include "Input.h"
#include "FadeToBlack.h"
#include "BattleManager.h"
#include "GuiManager.h"
#include "Textures.h"

#include "Player.h"
#include "Audio.h"

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

	player = app->battleManager->GetPlayer();
	for (int i = 0; i < player->GetBattleTeam().Count(); i++)
	{
		bars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, 40 + i, "XP", { player->GetBattleTeam().At(i)->data->GetPosition().x - 30,player->GetBattleTeam().At(i)->data->GetPosition().y - 30, 112, 9}, this));
		bars.At(i)->data->type = BarType::XP;
		SString xp("%i/%iXP", player->GetBattleTeam().At(i)->data->GetXP(), player->GetBattleTeam().At(i)->data->GetNextXP());
		texts.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 50 + i, xp.GetString(), { player->GetBattleTeam().At(i)->data->GetPosition().x + 115,player->GetBattleTeam().At(i)->data->GetPosition().y - 40, 155, 20 }, this, { 255, 255, 255, 255 }));
		SString lvl("%i LVL", player->GetBattleTeam().At(i)->data->GetLVL());
		lvls.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 50 + i, lvl.GetString(), { player->GetBattleTeam().At(i)->data->GetPosition().x,player->GetBattleTeam().At(i)->data->GetPosition().y - 70, 155, 20 }, this, { 255, 255, 255, 255 }));
		lvlUp.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 50 + i, "Level Up!", { player->GetBattleTeam().At(i)->data->GetPosition().x + 90,player->GetBattleTeam().At(i)->data->GetPosition().y - 70, 155, 20 }, this, { 255, 255, 255, 255 }, 0, true));
		lvlUp.At(i)->data->state = GuiControlState::DISABLED;
	}
	background = app->tex->Load("Assets/Textures/Sprites/battleback.png");
	app->audio->PlayFx(app->battleManager->battlewonSFX);
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
	

	if (XP >= 0)
	{
		
		for (int i = 0; i < player->GetBattleTeam().Count(); i++)
		{
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


	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->scene, 120);
	}
	app->render->DrawTexture(background, 0, 0);
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

	app->tex->UnLoad(background);
	lvls.Clear();
	texts.Clear();
	bars.Clear();


	return ret;
}
