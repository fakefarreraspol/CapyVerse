#include "EOBScene.h"

#include "App.h"

#include "Input.h"
#include "FadeToBlack.h"
#include "BattleManager.h"
#include "GuiManager.h"

#include "Player.h"

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
		bars.Add((GuiBar*)app->guiManager->CreateGuiControl(GuiControlType::BAR, 40 + i, "XP", { 170,i * 100 + 175, 155, 20 }, this));
		SString xp("%i/%iXP", player->GetBattleTeam().At(i)->data->GetXP(), player->GetBattleTeam().At(i)->data->GetNextXP());
		texts.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 50 + i, xp.GetString(), { 250, i * 100 + 175, 155, 20 }, this, { 255, 255, 255, 255 }));
		SString lvl("%i LVL", player->GetBattleTeam().At(i)->data->GetLVL());
		lvls.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 50 + i, lvl.GetString(), { 350, i * 100 + 175, 155, 20 }, this, { 255, 255, 255, 255 }));
		lvlUp.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 50 + i, "Level Up!", { 400, i * 100 + 175, 155, 20 }, this, { 255, 255, 255, 255 }, 0, true));
		lvlUp.At(i)->data->state = GuiControlState::DISABLED;
	}

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
			player->GetBattleTeam().At(i)->data->AddXp(1);
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

	
	lvls.Clear();
	texts.Clear();
	bars.Clear();


	return ret;
}
