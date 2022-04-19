#ifndef __GUIBAR_H__
#define __GUIBAR_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"
#include "GuiSliderBar.h"

class GuiBar : public GuiControl
{
public:
	GuiBar(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiBar();

	bool UpdateValues(int value, int maxValue);

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
