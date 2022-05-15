#ifndef __INTRO_H__
#define __INTRO_H__

#include "Module.h"

#include "Animation.h"
#include "Timer.h"

struct SDL_Texture;

class Intro : public Module
{
public:

	Intro(bool startEnabled);

	// Destructor
	virtual ~Intro();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


private:
	SDL_Texture* logo = nullptr;
	SDL_Texture* upc = nullptr;
	SDL_Texture * phrase = nullptr;
	Timer counter;
	int introSFX;
	bool sound = true;

	int upcCurrentTime = 0;
	int upcDuration = 300;
	int upcStartPositionX = -300;
	int upcFinalPositionX = 0;
	int upcCurrentPositionX = upcStartPositionX;


	int logoCurrentTime = 0;
	int logoDuration = 200;
	int logoStartPositionY = 500;
	int logoFinalPositionY = 0;
	int logoCurrentPositionY = logoStartPositionY;

	int phraseCurrentTime = 0;
	int phraseDuration = 200;
	int phraseStartPositionY = 500;
	int phraseFinalPositionY = 0;
	int phraseCurrentPositionY = phraseStartPositionY;
};

#endif // __INTRO_H__
