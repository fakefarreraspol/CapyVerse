#include "GuiSliderBar.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"

GuiSliderBar::GuiSliderBar(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::SLIDERBAR, id)
{
	this->bounds = bounds;
	this->text = text;

	drawBasic = false;
	state = GuiControlState::NORMAL;
}

GuiSliderBar::~GuiSliderBar()
{

}

bool GuiSliderBar::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiSliderBar::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:		render->DrawRectangle(bounds, 0, 0, 0, 0);			break;
	case GuiControlState::NORMAL:		render->DrawRectangle(bounds, 255, 0, 0, 255);		break;
	case GuiControlState::FOCUSED:		render->DrawRectangle(bounds, 255, 255, 255, 160);	break;
	//case GuiControlState::PRESSED:		render->DrawRectangle(bounds, 255, 255, 255, 255);	break;

	//case GuiControlState::SELECTED:		render->DrawRectangle(bounds, 0, 255, 0, 255);		break;

	default:
		break;
	}

	return false;
}