#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "Fonts.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	textTex = app->fonts->LoadRenderedText(bounds, app->fonts->globalFont, text, { 0, 0, 0, 1 });

	canClick = true;
	drawBasic = false;
}

GuiButton::~GuiButton()
{
	RELEASE(textTex);
	RELEASE(texture);
}

bool GuiButton::Update(float dt)
{
	GamePad& pad = app->input->pads[0];
	if (state != GuiControlState::DISABLED)
	{
		
		//// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		//int mouseX, mouseY;
		//app->input->GetMousePosition(mouseX, mouseY);

		//if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
		//	(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		//{
		//	state = GuiControlState::FOCUSED;

		//	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
		//	{
		//		state = GuiControlState::PRESSED;
		//	}

		//	// If mouse button pressed -> Generate event!
		//	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
		//	{
		//		NotifyObserver();
		//	}
		//}
		//else
		//	state = GuiControlState::NORMAL;

		if (state == GuiControlState::FOCUSED)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || pad.a)
			{
				state = GuiControlState::PRESSED;
				NotifyObserver();
			}
		}
	}


	return true;
}

bool GuiButton::Draw(Render* render)
{
	SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };
	// Draw the right button depending on state
	SDL_Rect disabled{ 0, 0, bounds.w, bounds.h };

	switch (state)
	{

	case GuiControlState::DISABLED:		render->DrawTexture(texture, cBounds.x, cBounds.y, &disabled);			break;
	case GuiControlState::NORMAL:		render->DrawTexture(texture, cBounds.x, cBounds.y, &disabled);			break;
	case GuiControlState::FOCUSED:		render->DrawTexture(texture, cBounds.x, cBounds.y, &disabled);			break;
	case GuiControlState::PRESSED:		render->DrawTexture(texture, cBounds.x, cBounds.y, &disabled);			break;
	case GuiControlState::SELECTED:		render->DrawTexture(texture, cBounds.x, cBounds.y, &disabled);			break;

	default:
		break;
	}

	if (app->GetDebug())
	{
		switch (state)
		{

		case GuiControlState::DISABLED:		render->DrawRectangle(cBounds, 0, 0, 0, 0);			break;
		case GuiControlState::NORMAL:		render->DrawRectangle(cBounds, 255, 0, 0, 255);		break;
		case GuiControlState::FOCUSED:		render->DrawRectangle(cBounds, 255, 255, 255, 160);	break;
		case GuiControlState::PRESSED:		render->DrawRectangle(cBounds, 255, 255, 255, 255);	break;
		case GuiControlState::SELECTED:		render->DrawRectangle(cBounds, 0, 255, 0, 255);		break;

		default:
			break;
		}
	}

	render->DrawTexture(textTex, cBounds.x, cBounds.y);

	return true;
}