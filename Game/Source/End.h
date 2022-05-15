#ifndef __END_H__
#define __END_H__

#include "Module.h"

#include "Animation.h"
#include "Timer.h"

struct SDL_Texture;

class End : public Module
{
public:

	End(bool startEnabled);

	// Destructor
	virtual ~End();

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
	SDL_Texture* background = nullptr;
};

#endif // __End_H__