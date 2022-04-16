#include "GuiBar.h"


#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"

GuiBar::GuiBar(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BAR, id)
{
	this->bounds = bounds;
	this->text = text;

	drawBasic = false;
}

GuiBar::~GuiBar()
{
}

bool GuiBar::UpdateValues(int value, int maxValue)
{
	bar.x = bounds.x;
	bar.y = bounds.y;
	float percentage = static_cast<float>(value) / maxValue;
	bar.w = bounds.w * percentage;
	bar.h = bounds.h;

	return true;
}




bool GuiBar::Update(float dt)
{
	return true;
}

bool GuiBar::Draw(Render* render)
{
	if (state != GuiControlState::DISABLED)
	{
		SDL_Rect cBar{ bar.x - render->camera.x, bar.y - render->camera.y, bar.w, bar.h };
		SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };
		render->DrawRectangle(cBounds, 150, 0, 0);
		render->DrawRectangle(cBar, 0, 150, 0);
	}
	return true;
}
