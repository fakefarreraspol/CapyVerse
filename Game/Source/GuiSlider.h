#ifndef GUISLIDER_H
#define GUISLIDER_H

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "GuiSliderBar.h"

class GuiSlider : public GuiControl
{
public:
	GuiSlider(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiSlider();
	
	bool SetBar(SDL_Rect bar);
	bool SetValues(int max, int min, int initial);

	bool Update(float dt);
	bool Draw(Render* render);

public:
	bool drawBasic = false;
	int value;

private:
	SDL_Rect bar;
	bool horizontal = true;
	int maxVal;
	int minVal;
};

#endif