#include <stdio.h>

#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"

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
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	img = app->tex->Load("Assets/Textures/test.png");
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");
	
	ent = app->entMan->CreateEntity(CapybaraType::DPS, 1, {20, 20}, "Emobara");
	ent1 = app->entMan->CreateEntity(CapybaraType::TANK , 1, { 40, 40 }, "Chinabara");
	ent2 = app->entMan->CreateEntity(CapybaraType::SUPP, 1, { 60, 60 }, "Punkibara");

	/*btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { 0, 0, 500, 100 }, this);
	slider1 = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 1, "dadf", { 0,0,50,50 }, this);
	slider1->SetBar({200,200,500,30});
	slider1->SetValues(100, 0, 0);
	slider1->state = GuiControlState::NORMAL;*/

	box1 = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 1, "", { 100,100,100,100 }, this);
	iPoint sexo = { 0,0 };
	app->entMan->CreateEntity(EntityType::PLAYER, 1, sexo, "sexo");
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
	
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	app->render->DrawTexture(img, 380, 100);

	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		ent->Attack(ent1);
		printf("%s DMG: %i %s HP: %i of %i\n", ent->name.GetString(), ent->GetDamage(), ent1->name.GetString(), ent1->GetHealth(), ent1->GetMaxHealth());
	}
	if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		ent->Attack(ent2);
		printf("%s DMG: %i %s HP: %i of %i\n", ent->name.GetString(), ent->GetDamage(), ent2->name.GetString(), ent2->GetHealth(), ent2->GetMaxHealth());
	}

	app->guiManager->Draw();

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

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
