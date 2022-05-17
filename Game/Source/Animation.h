#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 50

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES] = { 0 };
	Animation* ref = nullptr;
	bool loop = true;
	// Allows the animation to keep going back and forth
	bool pingpong = false;

private:
	int currentFrame = 0;
	int totalFrames = 0;
	int loopCount = 0;
	int pingpongDirection = 1;
	bool mustFlip = false;

public:
	Animation(){}
	~Animation(){}

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void SetAnim(Animation newAnim)
	{
		for (int i = 0; i < MAX_FRAMES; i++)
		{
			frames[i] = newAnim.frames[i];
		}
		ref = &newAnim;
	}

	void Reset()
	{
		currentFrame = 0;
	}

	bool HasFinished()
	{
		return !loop && !pingpong && loopCount > 0;
	}

	void Update()
	{
		currentFrame += speed;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop || pingpong) ? 0.0f : (float)(totalFrames - 1);
			++loopCount;

			if (pingpong)
				pingpongDirection = -pingpongDirection;
		}
	}

	const SDL_Rect& GetCurrentFrame() const
	{
		int actualFrame = currentFrame;
		if (pingpongDirection == -1)
			actualFrame = totalFrames - currentFrame;

		return frames[actualFrame];
	}
};

#endif
