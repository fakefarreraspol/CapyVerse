#include <stdio.h>

#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "FadeToBlack.h"
#include "BattleManager.h"
#include "Fonts.h"
#include "Map.h"

#include "Collisions.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "Player.h"

#include "Dialog.h"
#include "DialogManager.h"
#include "DialogNode.h"
#include "Pause.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"
#include "NPC.h"

Scene::Scene(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& node)
{
	LOG("Loading Scene");
	bool ret = true;
	
	player = (Player*)app->entMan->CreateEntity(EntityType::PLAYER, 1, { 0, 0 }, "Player");

	player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 2, { 100, 150 }, "Chinabara"));
	player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 3, { 100, 250 }, "Punkibara"));
	player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 4, { 100, 350 }, "Rainbowbara"));

	player->Disable();
	NPCs.Add(app->entMan->CreateEntity(EntityType::NPC, 10, { 200,200 }, "NPC"));
	NPCs.Add(app->entMan->CreateEntity(EntityType::NPC, 10, { 350,500 }, "NPC"));
	NPCs.Add(app->entMan->CreateEntity(EntityType::NPC, 10, { 400,120 }, "NPC"));

	


	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->pauseMenu->Enable();
	player->Enable();
	player->SetCombat(false);
	app->battleManager->SetPlayer(player);

	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Enable();
	}
	app->mapManager->Load("1-1.tmx");
	
	app->audio->ChangeMusic(2);
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	app->mapManager->Draw();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	

	return ret;
}

void Scene::OnCollision(Collider* c1, Collider* c2)
{
	
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->guiManager->Disable();
	app->pauseMenu->Disable();
	return true;
}
