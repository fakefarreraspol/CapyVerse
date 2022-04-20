#include "GuiBar.h"


#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiManager.h"
#include "Textures.h"

GuiBar::GuiBar(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BAR, id)
{
	this->bounds = bounds;
	this->text = text;

	drawBasic = false;
	texture = app->tex->Load("Assets/Menus/bars.png");
}

GuiBar::~GuiBar()
{
}

bool GuiBar::UpdateValues(int value, int maxValue)
{
	bar.x = bounds.x;
	bar.y = bounds.y;
	float percentage = static_cast<float>(value) / maxValue;
	bar.w = bounds.w * percentage;
	bar.h = bounds.h;

	return true;
}




bool GuiBar::Update(float dt)
{
	return true;
}

bool GuiBar::Draw(Render* render)
{
	if (state != GuiControlState::DISABLED)
	{
		SDL_Rect cBar{ bar.x - render->camera.x, bar.y - render->camera.y, bar.w, bar.h };
		SDL_Rect cBounds{ bounds.x - render->camera.x,bounds.y - render->camera.y,bounds.w,bounds.h };
		if (app->GetDebug())
		{
			render->DrawRectangle(cBounds, 150, 0, 0);
			render->DrawRectangle(cBar, 0, 150, 0);
		}
		switch (type)
		{
		case BarType::NONE:
			break;
		case BarType::HEALTH:
		{
			SDL_Rect cbar{ 0, 9, cBounds.w, cBounds.h };
			render->DrawTexture(texture, cBounds.x, cBounds.y, &cbar);
			SDL_Rect cbounds{ 0, 0, cBar.w, cBar.h };
			render->DrawTexture(texture, cBar.x, cBar.y, &cbounds);
		}break;
		case BarType::MANA:
		{
			SDL_Rect cbar{ 0, 30, cBounds.w, cBounds.h };
			render->DrawTexture(texture, cBounds.x, cBounds.y, &cbar);
			SDL_Rect cbounds{ 0, 18, cBar.w, cBar.h };
			render->DrawTexture(texture, cBar.x, cBar.y, &cbounds);
		}break;
		case BarType::XP:
		{
			SDL_Rect cbar{ 0, 51, cBounds.w, cBounds.h };
			render->DrawTexture(texture, cBounds.x, cBounds.y, &cbar);
			SDL_Rect cbounds{ 0, 42, cBar.w, cBar.h };
			render->DrawTexture(texture, cBar.x, cBar.y, &cbounds);
		}break;
		default:
			break;
		}
	}
	return true;
}
