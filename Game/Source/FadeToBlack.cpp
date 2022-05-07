#include "FadeToBlack.h"

#include "App.h"
#include "Render.h"
#include "Window.h"
#include "Transitions.h"

#include "SDL/include/SDL_render.h"

FadeToBlack::FadeToBlack(bool startEnabled) : Module(startEnabled)
{
	name.Create("fadetoblack");
}

FadeToBlack::~FadeToBlack()
{

}

bool FadeToBlack::Awake(pugi::xml_node&)
{
	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	screenRect = { 0, 0,  (int)winWidth * (int)app->win->GetScale(), (int)winHeight * (int)app->win->GetScale() };

	return true;
}

bool FadeToBlack::Start()
{
	//LOG("Preparing Fade Screen");
	app->win->GetWindowSize(w, h);
	screenRect = { 0, 0, (int)w, (int)h };
	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool FadeToBlack::Update(float dt)
{
	// Exit this function if we are not performing a fade
	if (currentStep == FadeStep::NONE) return true;

	if (currentStep == FadeStep::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			// L10: DONE 1: Enable / Disable the modules received when FadeToBlack() gets called
			moduleToDisable->Disable();
			moduleToEnable->Enable();

			currentStep = FadeStep::FROM_BLACK;
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = FadeStep::NONE;
		}
	}

	return true;
}

bool FadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == FadeStep::NONE) return true;


	
	//float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	//// Render the black square with alpha on the screen
	//SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	//SDL_RenderFillRect(app->render->renderer, &screenRect);

	return true;
}

bool FadeToBlack::MFadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames, uint16_t transitionID)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if (currentStep == FadeStep::NONE)
	{
		currentStep = FadeStep::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;
		app->transitions->SelectTransition(transitionID, 0, maxFadeFrames - 10);
		ret = true;
	}

	return ret;
}