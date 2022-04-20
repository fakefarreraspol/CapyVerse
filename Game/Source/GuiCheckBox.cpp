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
	texture = app->tex->Load("Assets/Menus/checkbox.png");
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
		if (app->GetDebug())
		{
			switch (state)
			{

			case GuiControlState::DISABLED:		break;
			case GuiControlState::NORMAL:		render->DrawRectangle(Bounds, 255, 0, 0, 255);		break;
			case GuiControlState::PRESSED:		render->DrawRectangle(Bounds, 255, 255, 255, 255);	break;


			default:
				break;
			}

		}
		SDL_Rect uncheck{ 0, 0, 25, 25 };
		SDL_Rect check{ 0, 25, 25, 25 };
		switch (state)
		{
		case GuiControlState::DISABLED:		break;
		case GuiControlState::NORMAL:		render->DrawTexture(texture, Bounds.x, Bounds.y,&uncheck);		break;
		case GuiControlState::PRESSED:		render->DrawTexture(texture, Bounds.x, Bounds.y, &check);	break;
		default:
			break;
		}
		app->render->DrawTexture(textTex, cBounds.x, cBounds.y);
	}
	return true;
}