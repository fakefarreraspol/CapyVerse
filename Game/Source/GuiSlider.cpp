#include "GuiSlider.h"

#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;

	drawBasic = false;
}

GuiSlider::~GuiSlider()
{
	RELEASE(textTex);
	RELEASE(texture);
}

bool GuiSlider::SetBar(SDL_Rect bar)
{
	this->bar = bar;

	if (bar.w > bar.h)
		horizontal = true;
	else
		horizontal = false;

	bounds.x = bar.x + (bar.w / 2) - (bounds.w / 2);
	bounds.y = bar.y + (bar.h / 2) - (bounds.h / 2);

	return true;
}

bool GuiSlider::SetValues(int max, int min, int initial)
{
	if (max > min)
	{
		maxVal = max;
		minVal = min;
		value = initial;

		if (value > maxVal)
			value = maxVal;
		if (value < minVal)
			value = minVal;

		if (horizontal == true)
			bounds.x = bar.x + (value * (maxVal - minVal) / bar.w) - bounds.w / 2;
		else
			bounds.y = bar.y + (value * (maxVal - minVal) / bar.h) - bounds.h / 2;
	}
	else
		return false;

	return true;
}

bool GuiSlider::Update(float dt)
{

	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if (state == GuiControlState::NORMAL)
		{
			if ((mouseX > bar.x) && (mouseX < (bar.x + bar.w)) &&
				(mouseY > bar.y) && (mouseY < (bar.y + bar.h)))
			{
				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::PRESSED;
					app->guiManager->SetActiveControll(this);
				}
			}
		}
		if (state == GuiControlState::PRESSED)
		{
			if (horizontal == true)
			{
				bounds.x = mouseX - bounds.w / 2;
				if (bounds.x < bar.x - bounds.w / 2)
					bounds.x = bar.x - bounds.w / 2;
				if (bounds.x > bar.x + bar.w - bounds.w / 2)
					bounds.x = bar.x + bar.w - bounds.w / 2;
				value = (bounds.x + bounds.w / 2 - bar.x) * (maxVal - minVal) / bar.w;
			}
			else
			{
				bounds.y = mouseY - bounds.h / 2;
				if (bounds.y < bar.y - bounds.h / 2)
					bounds.y = bar.y - bounds.h / 2;
				if (bounds.y < bar.y + bar.h - bounds.h / 2)
					bounds.y = bar.y + bar.h - bounds.h / 2;
				value = (bounds.y + bounds.h / 2 - bar.y) * (maxVal - minVal) / bar.h;

			}
			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
				app->guiManager->SetActiveControll(nullptr);
				state = GuiControlState::NORMAL;
			}
		}

	}
	return true;
}

bool GuiSlider::Draw(Render* render)
{
	iPoint offset = { render->camera.x,render->camera.y };
	
	if (state != GuiControlState::DISABLED)
	{
		SDL_Rect cBar{ bar.x - render->camera.x, bar.y - render->camera.y, bar.w, bar.h };
		SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };
		render->DrawRectangle(cBar, 255, 255, 255, 160);
		render->DrawRectangle(cBounds, 255, 255, 255, 160);


	}
	return true;
}