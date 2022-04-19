#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, const char* text, SDL_Color color = {0, 0, 0, 1}, int textID = 0);
	virtual ~GuiButton();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;
private:
	SDL_Texture* texture = nullptr;
	int sfx;
};

#endif // GUIBUTTON_H