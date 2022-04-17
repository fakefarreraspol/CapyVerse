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


#include "Defs.h"
#include "Log.h"

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

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	player->Enable();
	player->SetCombat(false);
	app->battleManager->SetPlayer(player);

	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Enable();
	}

	app->entMan->CreateEntity(EntityType::NPC, 0, { 200,200 }, "NPC");

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

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->battleScene1, 120);

	//app->guiManager->Draw();


	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		
		app->audio->PlayMusicSpatially({ 200, 200 });
	}

	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
	{
		LOG("W");
		app->audio->PlayMusic("Assets/Audio/Music/orslok-rojuu-tofu-delivery.wav");
		//app->audio->ChangeMusic(2);
	}
	
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

void Scene::OnCollision(Collider* c1, Collider* c2)
{
	printf("Collision\n");
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->guiManager->Disable();

	return true;
}
