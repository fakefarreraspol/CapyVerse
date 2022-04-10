#include "GuiText.h"

#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "Fonts.h"

GuiText::GuiText(uint32 id, SDL_Rect bounds, const char* text, SDL_Color color_) : GuiControl(GuiControlType::TEXT, id)
{
	this->bounds = bounds;
	this->text = text;
	this->color = color_;

	textTex = app->fonts->LoadRenderedText(bounds, app->fonts->globalFont, text, color);
}

GuiText::~GuiText()
{
	RELEASE(textTex);
	RELEASE(texture);
}


bool GuiText::Update(float dt)
{
	return true;
}

bool GuiText::SetText(const char* text)
{
	SDL_Rect tmpBounds = bounds;
	this->text = text;
	textTex = app->fonts->LoadRenderedText(tmpBounds, app->fonts->globalFont, text, color);
	return true;
}

bool GuiText::Draw(Render* render)
{
	if(state!=GuiControlState::DISABLED)
		render->DrawTexture(textTex, bounds.x, bounds.y);
	return true;
}

const char* GuiText::GetText()
{
	return this->text.GetString();
}
