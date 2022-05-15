#include "Intro.h"

#include "App.h"
#include "FadeToBlack.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Audio.h"
#include "easings.h"
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
	logo = app->tex->Load("Assets/Menus/logo.png");
	upc = app->tex->Load("Assets/Menus/UPC.png");
	phrase = app->tex->Load("Assets/Menus/phrase.png");
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
	if (sound)
	{
		app->audio->PlayFx(introSFX);
		sound = false;
	}
	
	if (upcCurrentPositionX < upcFinalPositionX)
	{
		upcCurrentPositionX = EaseQuadOut(upcCurrentTime, upcStartPositionX, upcFinalPositionX - upcStartPositionX, upcDuration);
		upcCurrentTime++;
	}
	if (logoCurrentPositionY > logoFinalPositionY)
	{
		logoCurrentPositionY = EaseBackOut(logoCurrentTime, logoStartPositionY, logoFinalPositionY - logoStartPositionY, logoDuration);
		logoCurrentTime++;
	}
	if (phraseCurrentPositionY > phraseFinalPositionY)
	{
		phraseCurrentPositionY = EaseBounceOut(phraseCurrentTime, phraseStartPositionY, phraseFinalPositionY - phraseStartPositionY, phraseDuration);
		phraseCurrentTime++;
	}

	printf("LOGO:%i, UPC:%i, PHRASE:%i\n", logoCurrentPositionY, upcCurrentPositionX, phraseCurrentPositionY);

	GamePad& pad = app->input->pads[0];
	if (counter.ReadSec() >= 10 || app->input->GetKey(SDL_SCANCODE_RETURN) || pad.a == true)
	{
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->mainMenu);
	}

	app->render->DrawTexture(logo, 0, logoCurrentPositionY);
	app->render->DrawTexture(upc, upcCurrentPositionX, 0);
	app->render->DrawTexture(phrase, 0, phraseCurrentPositionY);
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
