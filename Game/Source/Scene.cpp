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
#include "Enemy.h"
#include "Lever.h"
#include "Bridge.h"

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

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
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

	for (int i = 0; i < NPCs.Count(); i++)
	{
		NPCs.At(i)->data->Enable();
	}
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


bool Scene::LoadState(pugi::xml_node& data)
{

	ListItem<NPC*>* currNpc = NPCs.start;
	while (currNpc != NULL)
	{
		pugi::xml_node npcData = data.child("NPCs").child(currNpc->data->capyName.GetString());

		if ((EntityType)currNpc->data->type == EntityType::ENEMY)
		{
			Enemy* enemy = (Enemy*)currNpc->data;
			enemy->LoadState(npcData);
		}
		else currNpc->data->LoadState(npcData);

		currNpc = currNpc->next;
	}
	
	ListItem<Lever*>* lever = levers.start;
	pugi::xml_node leverData = data.child("LEVERS").first_child();
	while (lever && leverData)
	{
		if (leverData.attribute("activated").as_bool() == true)
		{
			lever->data->activated = true;
			lever->data->currentAnim = &(lever->data->open);
		}
		else
		{
			lever->data->activated = false;
			lever->data->currentAnim = &(lever->data->closed);
		}

		lever = lever->next;
		leverData = leverData.next_sibling();
	}

	bridge->Start();
	bridge->counter = data.child("bridge").attribute("counter").as_int();
	
	

	player->LoadState(data.child("player"));



	return true;
}
bool Scene::SaveState(pugi::xml_node& data) const
{
	// NPCS
	pugi::xml_node npcs = data.append_child("NPCs");
	ListItem<NPC*>* npc = NPCs.start;
	while (npc!=NULL)
	{
		pugi::xml_node npcData = npcs.append_child(npc->data->capyName.GetString());
		if (npc->data->type==EntityType::NPC)
			npc->data->SaveState(npcData);
		else
		{
			Enemy* enemy = (Enemy*)npc->data;
			enemy->SaveState(npcData);
		}

		npc = npc->next;
	}

	// LEVERS
	pugi::xml_node leversData = data.append_child("LEVERS");
	ListItem<Lever*>* lever = levers.start;
	while (lever!=NULL)
	{
		pugi::xml_node leverData = data.append_child("lever");
		leverData.append_attribute("id").set_value(lever->data->id);
		leverData.append_attribute("activated").set_value(lever->data->activated);

		lever = lever->next;
	}

	// BRIDGE
	if (bridge!=nullptr)
	{
		bool activated = false;
		pugi::xml_node bridgeData = data.append_child("bridge");
		bridgeData.append_attribute("counter").set_value(bridge->counter);
	}

	// PLAYER
	if (player)
	{
		pugi::xml_node playerData = data.append_child("player");
		player->SaveState(playerData);
	}

	return true;
}