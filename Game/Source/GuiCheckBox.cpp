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
	bool ret = true;
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);
		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;
			

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				checked = !checked;
				ret = NotifyObserver();
			}
		}
		else
		{
			state = GuiControlState::NORMAL;
		}

	}

	return ret;
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
	}
	return true;
}