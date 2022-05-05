#include "Transitions.h"
#include "App.h"
#include "Render.h"
#include "easings.h"
#include "Window.h"
#include "Textures.h"
#include <SDL_image/include/SDL_image.h>
#include <iostream>

using namespace std;

Transitions::Transitions(bool startEnabled) : Module(startEnabled)
{
	name.Create("battle_transitions");
}

Transitions::~Transitions() {}

bool Transitions::Start()
{

	texture = app->tex->Load("Assets/textures/eyes.png");
	pokeball = app->tex->Load("Assets/textures/Pokeball.png");
	app->win->GetWindowSize(win_width, win_height);

	return true;
}
bool Transitions::Update(float dt)
{
	bool ret = true;


	return ret;
}
bool Transitions::PostUpdate()
{
	bool ret = true;


	switch (currentStep)
	{
	case Transitions::NONE:

		break;
	case Transitions::TRANSTITION:


		timer_in_transition++;

		if (animationSelected == 1)
		{
			DrawTransition1();
		}
		if (animationSelected == 2)
		{
			DrawTransition2();
		}
		if (animationSelected == 3)
		{
			DrawTransition3();
		}
		if (animationSelected == 4)
		{
			DrawTransition4();
		}

		if (timer_in_transition >= timer_out_transition)
		{
			currentStep = Fade_Step::FROM_TRANSITION;
		}

		break;
	case Transitions::FROM_TRANSITION:

		timer_out_transition--;

		if (animationSelected == 1)
		{
			DrawTransition1();
		}
		if (animationSelected == 2)
		{
			DrawTransition2();
		}
		if (animationSelected == 3)
		{
			DrawTransition3();
		}
		if (animationSelected == 4)
		{
			DrawTransition4();
		}

		if (timer_out_transition <= 0)
		{
			currentStep = Fade_Step::NONE;
		}

		break;
	default:
		break;
	}

	return ret;

}

void Transitions::SelectTransition(int id, int timer1, int timer2)
{
	if (currentStep == Fade_Step::NONE)
	{
		timer_in_transition = timer1;
		timer_out_transition = timer2;
		currentStep = Fade_Step::TRANSTITION;
		animationSelected = id;
	}
}

void Transitions::DrawTransition1()
{
	//SLIDE TRANSITION

	SDL_Rect Rect1;

	Rect1.x = 0;
	Rect1.y = 0;
	Rect1.h = win_height;
	Rect1.w = 0;

	if (currentStep == Fade_Step::TRANSTITION) Rect1.w = EaseLinearInOut(timer_in_transition, win_width / 64, win_width, 30);
	if (currentStep == Fade_Step::FROM_TRANSITION) Rect1.w = EaseLinearInOut(timer_out_transition, win_width / 64, win_width, 30);
	app->render->DrawRectangle(Rect1, 255, 0, 0, 255, true, false);

}

void Transitions::DrawTransition2()
{
	SDL_Rect Rect1;
	SDL_Rect Rect2;
	SDL_Rect Rect3;
	SDL_Rect Rect4;

	Rect1.x = 0;  Rect2.x = win_width;  Rect3.x = 0; Rect4.x = win_width;
	Rect1.y = 0;
	Rect2.y = win_height / 4;
	Rect3.y = (win_height / 4) * 2;
	Rect4.y = (win_height / 4) * 3;
	Rect1.h = win_height / 4; Rect2.h = win_height / 4; Rect3.h = win_height / 4; Rect4.h = win_height / 4;

	if (currentStep == Fade_Step::TRANSTITION)
	{
		Rect1.w = EaseLinearIn(timer_in_transition, win_width / 64, win_width, 30);
		Rect2.w = -EaseLinearIn(timer_in_transition, win_width / 64, win_width, 30);
		Rect3.w = EaseLinearIn(timer_in_transition, win_width / 64, win_width, 30);
		Rect4.w = -EaseLinearIn(timer_in_transition, win_width / 64, win_width, 30);
	}
	if (currentStep == Fade_Step::FROM_TRANSITION)
	{
		Rect1.w = EaseLinearIn(timer_out_transition, win_width / 64, win_width, 30);
		Rect2.w = -EaseLinearIn(timer_out_transition, win_width / 64, win_width, 30);
		Rect3.w = EaseLinearIn(timer_out_transition, win_width / 64, win_width, 30);
		Rect4.w = -EaseLinearIn(timer_out_transition, win_width / 64, win_width, 30);
	}

	app->render->DrawRectangle(Rect1, 255, 0, 0, 255, true, false);
	app->render->DrawRectangle(Rect2, 0, 255, 0, 255, true, false);
	app->render->DrawRectangle(Rect3, 0, 0, 255, 255, true, false);
	app->render->DrawRectangle(Rect4, 123, 0, 122, 255, true, false);


}

void Transitions::DrawTransition3()
{
	SDL_Rect Rect1;
	SDL_Rect Rect2;
	SDL_Rect Rect3;
	SDL_Rect Rect4;
	SDL_Rect Rect5;

	Rect1.x = 0;  Rect2.x = win_width;  Rect3.x = 0; Rect4.x = win_width; Rect5.x = 0;
	Rect1.y = 0;
	Rect2.y = win_height / 5;
	Rect3.y = (win_height / 5) * 2;
	Rect4.y = (win_height / 5) * 3;
	Rect5.y = (win_height / 5) * 4;
	Rect1.h = win_height / 5; Rect2.h = win_height / 5; Rect3.h = win_height / 5; Rect4.h = win_height / 5; Rect5.h = win_height / 5;
	if (currentStep == Fade_Step::TRANSTITION)
	{
		Rect1.w = EaseLinearIn(timer_in_transition / 8, win_width / 64, win_width, 240);
		Rect2.w = -EaseLinearIn(timer_in_transition / 8, win_width / 64, win_width, 240);
		Rect3.w = EaseLinearIn(timer_in_transition / 8, win_width / 64, win_width, 240);
		Rect4.w = -EaseLinearIn(timer_in_transition / 8, win_width / 64, win_width, 240);
		Rect5.w = EaseLinearIn(timer_in_transition / 8, win_width / 64, win_width, 240);

		app->render->DrawRectangle(Rect1, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect2, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect3, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect4, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect5, 255, 0, 0, 255);

		app->render->DrawTexture(pokeball, (Rect1.x + Rect1.w - 120), (Rect1.y - 10), NULL, 0, EaseLinearIn(timer_in_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect2.x + Rect2.w - 120), (Rect2.y - 10), NULL, 0, EaseLinearIn(timer_in_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect3.x + Rect3.w - 120), (Rect3.y - 10), NULL, 0, EaseLinearIn(timer_in_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect4.x + Rect4.w - 120), (Rect4.y - 10), NULL, 0, EaseLinearIn(timer_in_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect5.x + Rect5.w - 120), (Rect5.y - 10), NULL, 0, EaseLinearIn(timer_in_transition / 24, win_width / 64, win_width, 240));
	}
	if (currentStep == Fade_Step::FROM_TRANSITION)
	{
		Rect1.w = EaseLinearIn(timer_out_transition / 8, win_width / 64, win_width, 240);
		Rect2.w = -EaseLinearIn(timer_out_transition / 8, win_width / 64, win_width, 240);
		Rect3.w = EaseLinearIn(timer_out_transition / 8, win_width / 64, win_width, 240);
		Rect4.w = -EaseLinearIn(timer_out_transition / 8, win_width / 64, win_width, 240);
		Rect5.w = EaseLinearIn(timer_out_transition / 8, win_width / 64, win_width, 240);

		app->render->DrawRectangle(Rect1, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect2, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect3, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect4, 255, 0, 0, 255);
		app->render->DrawRectangle(Rect5, 255, 0, 0, 255);

		app->render->DrawTexture(pokeball, (Rect1.x + Rect1.w - 120), (Rect1.y - 10), NULL, 0, EaseLinearIn(timer_out_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect2.x + Rect2.w - 120), (Rect2.y - 10), NULL, 0, EaseLinearIn(timer_out_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect3.x + Rect3.w - 120), (Rect3.y - 10), NULL, 0, EaseLinearIn(timer_out_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect4.x + Rect4.w - 120), (Rect4.y - 10), NULL, 0, EaseLinearIn(timer_out_transition / 24, win_width / 64, win_width, 240));
		app->render->DrawTexture(pokeball, (Rect5.x + Rect5.w - 120), (Rect5.y - 10), NULL, 0, EaseLinearIn(timer_out_transition / 24, win_width / 64, win_width, 240));
	}

}

void Transitions::DrawTransition4()
{

	SDL_Rect Rect1;
	Rect1.x = 0;
	Rect1.y = 0;
	Rect1.w = win_width;
	Rect1.h = win_height;

	if (currentStep == Fade_Step::TRANSTITION) app->render->DrawRectangle(Rect1, timer_in_transition / 10, 0, 0, 255);
	if (currentStep == Fade_Step::FROM_TRANSITION) app->render->DrawRectangle(Rect1, timer_out_transition / 10, 0, 0, 255);


}