#include "GuiCheckBox.h"

#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Fonts.h"
#include "Textures.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	textTex = app->fonts->LoadRenderedText(bounds, app->fonts->globalFont, text, {255, 255, 255, 1});
	checked = true;
}

GuiCheckBox::~GuiCheckBox()
{

}

bool GuiCheckBox::Update(float dt)
{
	GamePad& pad = app->input->pads[0];
	if (state != GuiControlState::DISABLED)
	{
		if (state == GuiControlState::FOCUSED)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || pad.a)
			{
				checked = !checked;
				NotifyObserver();
			}
		}
		if (checked == true)
			state = GuiControlState::PRESSED;
		if (checked == false)
			state = GuiControlState::NORMAL;
	}

	return true;
}

bool GuiCheckBox::Draw(Render* render)
{
	SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };

	// Draw the right button depending on state
	if (state != GuiControlState::DISABLED)
	{
		uint w, h;
		app->tex->GetSize(textTex,w, h);
		SDL_Rect Bounds{ cBounds.x + w + 50, cBounds.y, bounds.w, bounds.h};
		switch (state)
		{

		case GuiControlState::DISABLED:		render->DrawRectangle(Bounds, 0, 0, 0, 0);			break;
		case GuiControlState::NORMAL:		render->DrawRectangle(Bounds, 255, 0, 0, 255);		break;
		case GuiControlState::PRESSED:		render->DrawRectangle(Bounds, 255, 255, 255, 255);	break;


		default:
			break;
		}
		app->render->DrawTexture(textTex, cBounds.x, cBounds.y);
	}
	return true;
}