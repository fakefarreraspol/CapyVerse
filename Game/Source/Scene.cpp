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
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 800,300 }, "Sara"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 500,800 }, "Joe"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 900,700 }, "George"));

	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Disable();
	}

	NPCs.At(0)->data->dialog = new Dialog();
	DialogNode* fst0 = new DialogNode("Hello there you seem to be new here. Do you already have your capys?");
	DialogNode* sec0 = NPCs.At(0)->data->dialog->AddOption(fst0, "No, no problem I've got you!", "");
	DialogNode* thr0 = NPCs.At(0)->data->dialog->AddOption(sec0, "I'll give you mine. Here you go! But promise you wont sell them!", "");
	DialogNode* for0 = NPCs.At(0)->data->dialog->AddOption(thr0, "By the way, I run a shop on a town near by.", "");
	DialogNode* ft0 = NPCs.At(0)->data->dialog->AddOption(for0, "Today it's closed. But you can come later, I sell a lot of goodies for the capys!", "");
	NPCs.At(0)->data->dialog->AddFirstNode(fst0);

	NPCs.At(1)->data->dialog = new Dialog();
	DialogNode* fst1 = new DialogNode("Hey, do you know the ADMIN of this game?");
	DialogNode* sec1 = NPCs.At(0)->data->dialog->AddOption(fst1, "I think he is the richest one", "");
	DialogNode* thr1 = NPCs.At(0)->data->dialog->AddOption(sec1, "I wish i could be as him ^^", "");
	NPCs.At(1)->data->dialog->AddFirstNode(fst1);

	NPCs.At(2)->data->dialog = new Dialog();
	DialogNode* fst2 = new DialogNode("There are so many capybaras");
	DialogNode* sec2 = NPCs.At(2)->data->dialog->AddOption(fst2, "Gotta catch 'em all!!!!!!", "");
	NPCs.At(2)->data->dialog->AddFirstNode(fst2);

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
	for (uint16_t i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Disable();
	}
	app->mapManager->Disable();
	app->colManager->Disable();
	return true;
}
