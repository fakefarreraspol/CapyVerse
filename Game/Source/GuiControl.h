#ifndef __GUICONTROL_H__
#define __GUICONTROL_H__

#include "SDL/include/SDL.h"

#include "Input.h"
#include "Render.h"
#include "Module.h"

#include "Point.h"
#include "SString.h"


class GuiPanel;
enum class GuiControlType
{
	NONE = -1,
	BUTTON,
	CHECKBOX,
	SLIDER,
	BAR,
	SPINNER,
	TEXT
};

enum class GuiControlState
{
	NONE = -1,
	DISABLED,
	NORMAL,
	FOCUSED,
	PRESSED,
	SELECTED
};

class GuiControl
{
public:

	GuiControl(GuiControlType type, uint32 id) : type(type), id(id), state(GuiControlState::NORMAL) {}

	GuiControl(GuiControlType type, SDL_Rect bounds, const char* text) :
		type(type),
		state(GuiControlState::NORMAL),
		bounds(bounds),
		text(text)
	{
		color.r = 255; color.g = 255; color.b = 255;
		texture = NULL;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Draw(Render* render)
	{
		return true;
	}

	void SetTexture(SDL_Texture* tex)
	{
		texture = tex;
		section = { 0, 0, 0, 0 };
	}

	void SetObserver(Module* module)
	{
		observer = module;
	}
	void SetParent(GuiPanel* panel)
	{
		parent = panel;
	}
	bool NotifyObserver()
	{
		return observer->OnGuiMouseClickEvent(this);
	}

	virtual bool SetText(const char* text)
	{
		return true;
	}
	virtual bool CleanUp()
	{
		return true;
	}

public:

	uint32 id = 0;
	GuiControlType type = GuiControlType::NONE;
	GuiControlState state = GuiControlState::NONE;

	SString text;           // Control text (if required)
	SDL_Rect bounds = {0, 0, 0, 0};        // Position and size
	SDL_Color color = {0, 0, 0, 0};        // Tint color

	SDL_Texture* texture = nullptr;   // Texture atlas reference
	SDL_Texture* textTex = nullptr;
	SDL_Rect section = {0, 0, 0, 0};       // Texture atlas base section

	//Font font;              // Text font

	Module* observer = nullptr;        // Observer module (it should probably be an array/list)
	GuiPanel* parent;		//Panel where the element is located
};


#endif