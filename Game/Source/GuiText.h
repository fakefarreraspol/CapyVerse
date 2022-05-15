#ifndef __GUITEXT_H__
#define __GUITEXT_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiText : public GuiControl
{
public:

	GuiText(uint32 id, SDL_Rect bounds, const char* text, SDL_Color color, int fontID = 0,bool blink = false);
	virtual ~GuiText();

	bool Update(float dt);
	bool SetText(const char* text);
	bool Draw(Render* render);

	const char* GetText();


	bool useCamera = false;
private:
	bool blink = false;
	int font;
	int counter = 0;
};

#endif // __GUITEXT_H__
