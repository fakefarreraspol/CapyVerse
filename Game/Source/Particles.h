#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Module.h"

#include "Particle.h"
#include "Log.h"
#include "Point.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

class Particles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	Particles(bool startEnabled);

	//Destructor
	~Particles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	bool Update(float dt) override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	bool PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	// An index to the last added particle
	uint lastParticle = 0;

public:
	//Template particle for an explosion
	Particle explosion;

	//Template particle for a laser
	Particle laser;
};

#endif // !__Particles_H__
