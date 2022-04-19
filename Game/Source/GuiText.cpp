#include "GuiText.h"

#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "Fonts.h"


GuiText::GuiText(uint32 id, SDL_Rect bounds, const char* text, SDL_Color color_, int fontID, bool blink) : GuiControl(GuiControlType::TEXT, id)
{
	this->bounds = bounds;
	this->text = text;
	this->color = color_;
	this->blink = blink;
	this->counter = rand() % 60;

	if (fontID == 0)
		fontID = app->fonts->globalFont;
	textTex = app->fonts->LoadRenderedText(bounds, fontID, text, color);
}

GuiText::~GuiText()
{
	RELEASE(textTex);
	RELEASE(texture);
}


bool GuiText::Update(float dt)
{
	if(blink)
		counter++;

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
	SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };

	if (state != GuiControlState::DISABLED)
	{
		if (blink)
		{
			if ((counter / 30) % 2 == 0)
				render->DrawTexture(textTex, cBounds.x, cBounds.y);
		}
		else
			render->DrawTexture(textTex, cBounds.x, cBounds.y);
	}
	return true;
}

const char* GuiText::GetText()
{
	return this->text.GetString();
}
