#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class FadeToBlack : public Module
{
public:
	//Constructor
	FadeToBlack(bool startEnabled);

	//Destructor
	~FadeToBlack();


	bool Awake(pugi::xml_node&);
	// Called when the module is activated
	// Enables the blending mode for transparency
	bool Start();

	// Called at the middle of the application loop
	// Updates the fade logic
	bool Update(float dt);

	// Called at the end of the application loop
	// Performs the render call of a black rectangle with transparency
	bool PostUpdate();

	// Called from another module
	// Starts the fade process which has two steps, fade_out and fade_in
	// After the first step, the modules should be switched
	bool MFadeToBlack(Module* toDisable, Module* toEnable, uint16_t transitionID = 1, float frames = 60);

private:

	enum class FadeStep
	{
		NONE = -1,
		TO_BLACK,
		FROM_BLACK
	};
	FadeStep currentStep = FadeStep::NONE;

	// A frame count system to handle the fade time and ratio
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	// The rectangle of the screen, used to render the black rectangle
	SDL_Rect screenRect = {0, 0, 0, 0};

	// The modules that should be switched after the first step
	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;

	Uint32 h = 0, w = 0;
public:
	bool loadRequest = false;

};

#endif //__MODULEFADETOBLACK_H__