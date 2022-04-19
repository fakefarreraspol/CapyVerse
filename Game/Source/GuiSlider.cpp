#include "GuiSlider.h"

#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "Fonts.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;
	this->bar = bounds;
	textTex = app->fonts->LoadRenderedText(bounds, app->fonts->globalFont, text, { 255, 255, 255, 1 });

	drawBasic = false;
}

GuiSlider::~GuiSlider()
{
	RELEASE(textTex);
	RELEASE(texture);
}

bool GuiSlider::SetValues(int max, int min, int value)
{
	if (max > min)
	{
		maxVal = max;
		minVal = min;
		this->value = value;
	}
	return true;
}

bool GuiSlider::Update(float dt)
{
	GamePad& pad = app->input->pads[0];
	if (state != GuiControlState::DISABLED)
	{
		if (state == GuiControlState::FOCUSED)
		{
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.left)
			{
				if (value > 0)
				{
					value -= 10;
				}
			}
			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.right)
			{
				if (value < maxVal)
				{
					value += 10;
				}
				
			}
		}
	}
	bar.x = bounds.x;
	bar.y = bounds.y;
	float percentage = static_cast<float>(value) / maxVal;
	bar.w = bounds.w * percentage;
	bar.h = bounds.h;
	return true;
}

bool GuiSlider::Draw(Render* render)
{
	iPoint offset = { render->camera.x,render->camera.y };
	
	if (state != GuiControlState::DISABLED)
	{
		SDL_Rect cBar{ bar.x - render->camera.x, bar.y - render->camera.y, bar.w, bar.h };
		SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };
		render->DrawRectangle(cBounds, 0, 255, 255, 160);
		render->DrawRectangle(cBar, 255, 0, 255, 160);

		SDL_Rect bounds{ cBounds.x + cBounds.w + 50, cBounds.y, 0, 0 };
		app->render->DrawTexture(textTex, bounds.x, bounds.y);

	}
	return true;
}