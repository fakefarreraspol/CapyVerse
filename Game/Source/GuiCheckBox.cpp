#include "GuiCheckBox.h"

#include "Render.h"
#include "App.h"
#include "Audio.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	checked = true;
}

GuiCheckBox::~GuiCheckBox()
{

}

bool GuiCheckBox::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GuiCheckBox according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
			{
				checked =! checked;
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
	switch (state)
	{

	case GuiControlState::DISABLED:		render->DrawRectangle(cBounds, 0, 0, 0, 0);			break;
	case GuiControlState::NORMAL:		render->DrawRectangle(cBounds, 255, 0, 0, 255);		break;
	case GuiControlState::PRESSED:		render->DrawRectangle(cBounds, 255, 255, 255, 255);	break;


	default:
		break;
	}

	return true;
}