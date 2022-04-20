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
	
	player = (Player*)app->entMan->CreateEntity(EntityType::PLAYER, 1, { 640, 400 }, "Player");

	player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 2, { 291, 297 }, "Chinabara"));
	player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 3, { 101, 435 }, "Punkibara"));
	player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 4, { 464, 443 }, "Rainbowbara"));

	player->Disable();
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 300,200 }, "Farmer"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 350,500 }, "NPC"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 400,120 }, "NPC"));

	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Disable();
	}

	NPCs.At(0)->data->dialog = new Dialog();
	DialogNode* first = new DialogNode("Hello, and welcome to the Capyverse. Do you already have your capys?");
	NPCs.At(0)->data->dialog->AddFirstNode(first);
	DialogNode* sec = new DialogNode("No, no problem I've got you!");
	NPCs.At(0)->data->dialog->AddOption(first, sec);
	DialogNode* thr = new DialogNode("I'll give you mine. Here you go!");
	NPCs.At(0)->data->dialog->AddOption(sec, thr);


	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->pauseMenu->Enable();
	app->colManager->Enable();
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
	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Disable();
	}
	app->mapManager->Disable();
	app->colManager->Disable();
	return true;
}
