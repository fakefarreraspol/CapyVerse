#include "EOBScene.h"

#include "App.h"

#include "Input.h"
#include "FadeToBlack.h"
#include "BattleManager.h"

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

	player = app->battleManager->GetPlayer();

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

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->scene, 120);
		player->SetCombat(false);
	}

	return ret;
}

bool EOBScene::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool EOBScene::CleanUp()
{
	bool ret = true;
	return ret;
}
