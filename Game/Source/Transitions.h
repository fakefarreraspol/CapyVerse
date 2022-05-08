#ifndef __TRANSITIONS_H__
#define __TRANSITIONS_H__

#include "Module.h"
#include "Render.h"
#include "SDL/include/SDL_rect.h"

class Transitions : public Module
{
public:

	// Constructor
	Transitions(bool startEnabled);

	// Destructor
	virtual ~Transitions();

	// Called before the first frame
	bool Start();

	bool Update(float dt);

	bool PostUpdate();
	void SelectTransition(int id, float timer_in_transition, float timer_out_transition);
	//NEED TO CREATE MORE DRAWTRANSITIONS
	void DrawTransition1();
	void DrawTransition2();
	void DrawTransition3();
	void DrawTransition4();


public:

	enum Fade_Step
	{
		NONE,
		TRANSTITION,
		FROM_TRANSITION
	} currentStep = Fade_Step::NONE;

	int animationSelected = 0;
	float timer_in_transition = 0;
	float timer_out_transition = 0;
	uint win_width = 0;
	uint win_height = 0;

	// The rectangles of the screen, used to render the animation

	SDL_Texture* pokeball = nullptr;
	SDL_Texture* texture = nullptr;
};

#endif // __WINDOW_H__