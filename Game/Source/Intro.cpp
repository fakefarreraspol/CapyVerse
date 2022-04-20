#include "Intro.h"

#include "App.h"
#include "FadeToBlack.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Audio.h"
#include "Log.h"

Intro::Intro(bool startEnabled) : Module(startEnabled)
{
	name.Create("intro");
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake(pugi::xml_node& node)
{
	LOG("Loading Intro");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool Intro::Start()
{
	counter.Start();

	introSFX = app->audio->LoadFx("Assets/Audio/Fx/item-obtained.wav");
	background = app->tex->Load("Assets/Menus/intro.png");
	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
{
	app->render->DrawTexture(background, 0, 0);
	if (sound)
	{
		app->audio->PlayFx(introSFX);
		sound = false;
	}
	

	GamePad& pad = app->input->pads[0];
	if (counter.ReadSec() >= 4 || app->input->GetKey(SDL_SCANCODE_RETURN) || pad.a == true)
	{
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->mainMenu);
	}
	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool Intro::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
