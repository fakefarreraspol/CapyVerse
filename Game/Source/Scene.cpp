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
#include "QuestManager.h"

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
#include "Lever.h"
#include "Bridge.h"
#include "Shop.h"

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
	
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 512,1266 }, "Sara"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 1969,878 }, "Joe"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::NPC, 10, { 1200,700 }, "George"));
	NPCs.Add((NPC*)app->entMan->CreateEntity(EntityType::TRADER, 10, { 1100,700 }, "Sara"));


	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Disable();
	}

	NPCs.At(0)->data->dialog = new Dialog(1);
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

	NPCs.At(3)->data->dialog = new Dialog();
	DialogNode* fst3 = new DialogNode("Hey, take a look at what can I offer to you!");
	NPCs.At(3)->data->dialog->AddFirstNode(fst3);
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->shop->Enable();
	app->questManager->Enable();
	if (!bridge)
	{
		bridge = (Bridge*)app->entMan->CreateEntity(EntityType::BRIDGE, 0, { 2478, 870 }, "Bridge");
		bridge->Start();
		levers.Add((Lever*)app->entMan->CreateEntity(EntityType::LEVER, 0, { 2016, 350 }, ""));
		levers.Add((Lever*)app->entMan->CreateEntity(EntityType::LEVER, 0, { 2388, 1451 }, ""));
		levers.Add((Lever*)app->entMan->CreateEntity(EntityType::LEVER, 0, { 1649, 1251 }, ""));
		PhysBody* end= app->colManager->CreateRectangleSensor(2600, 870, 32, 128, bodyType::STATIC);
		end->listener = this;
	}
	bridge->Enable();
	for (int i = 0; i < levers.Count(); i++)
	{
		levers.At(i)->data->SetQuest(6);
		levers.At(i)->data->SetListener(bridge);
		levers.At(i)->data->Enable();
	}
	
	if (!player)
	{
		player = (Player*)app->entMan->CreateEntity(EntityType::PLAYER, 1, { 650, 1440 }, "Player");

		player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 2, { 291, 443 }, "Chinabara"));
		player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 3, { 101, 443 }, "Punkibara"));
		player->AddCapybaraToBatle(app->entMan->CreateEntity(CapybaraType::TANK, 4, { 464, 443 }, "Rainbowbara"));

		app->questManager->ActiveQuest(0);
	}
	player->Enable();
	player->canMove = true;
	app->pauseMenu->Enable();
	app->colManager->Enable();
	player->SetCombat(false);
	app->battleManager->SetPlayer(player);

	for (int i = 0; i < levers.Count(); i++)
	{
		levers.At(i)->data->Enable();
	}
	app->mapManager->Load("1-1.tmx");
	
	app->audio->ChangeMusic(2);

	if (load)
	{
		app->LoadGameRequest();
		load = false;
	}
	app->dialogManager->Enable();

	if (app->questManager->IsCompleated(1))
	{
		app->questManager->ActiveQuest(2);
	}
	if (app->questManager->IsCompleated(2))
	{
		app->questManager->ActiveQuest(6);
	}

	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Enable();
	}

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

	if (app->dialogManager->activeDialog == NPCs.At(0)->data->dialog)
	{
		app->questManager->CompleteQuest(0);
	}

	return true;
}

void Scene::OnCollision(PhysBody* c1, PhysBody* c2)
{
	if (c2->eListener->type == EntityType::PLAYER && end)
	{
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->end, 1);
		end = false;
	}

}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	

	return ret;
}



// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->guiManager->Disable();
	app->pauseMenu->Disable();
	app->questManager->Disable();
	for (uint16_t i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Disable();
	}
	for (int i = 0; i < levers.Count(); i++)
	{
		levers.At(i)->data->Disable();
	}
	player->Disable();
	bridge->Disable();
	app->mapManager->Unload();


	LOG("Succesfully unloaded scene");
	return true;
}
