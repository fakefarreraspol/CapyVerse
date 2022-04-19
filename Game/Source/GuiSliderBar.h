#ifndef GUISLIDERBAR_H
#define GUISLIDERBAR_H

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSliderBar : public GuiControl
{
public:
	GuiSliderBar(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiSliderBar();

	bool Update(float dt);
	bool Draw(Render* render);

public:
	bool drawBasic = false;

};

#endif