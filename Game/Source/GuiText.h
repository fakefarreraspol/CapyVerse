#ifndef __GUITEXT_H__
#define __GUITEXT_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiText : public GuiControl
{
public:

	GuiText(uint32 id, SDL_Rect bounds, const char* text, SDL_Color color);
	virtual ~GuiText();

	bool Update(float dt);
	bool SetText(const char* text);
	bool Draw(Render* render);

	const char* GetText();
};

#endif // __GUITEXT_H__
