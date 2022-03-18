#ifndef GUICHECKBOX_H
#define GUICHECKBOX_H

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

	GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiCheckBox();

	bool Update(float dt);
	bool Draw(Render* render);

public:

	bool checked = true;
};







#endif