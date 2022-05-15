#include "Lever.h"
#include "App.h"
#include "Input.h"
#include "Physics.h"
#include "GuiManager.h"
#include "Fonts.h"
#include "QuestManager.h"
#include "Textures.h"

Lever::Lever(iPoint position, uint32_t id, uint32_t questID) : Entity(EntityType::LEVER, id, "Lever", position), questID(questID)
{
	trigger = app->colManager->CreateRectangleSensor(position.x, position.y, 64, 64, bodyType::STATIC);
	trigger->eListener = this;
	trigger->listener = (Module*)app->entMan;
	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	text = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "Press E to switch", { position.x - 50, position.y + 32, 100, 100 }, nullptr, { 255, 255, 255, 1 }, app->fonts->indicatorsFont);
	text->state = GuiControlState::DISABLED;
}

Lever::~Lever()
{
}

bool Lever::Start()
{
	if (!trigger)
	{
		trigger = app->colManager->CreateRectangleSensor(position.x, position.y, 64, 64, bodyType::STATIC);
		trigger->eListener = this;
		trigger->listener = (Module*)app->entMan;
	}
	if(!collider)
		collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	if(!text)
		text = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "Press E to switch", { position.x - 50, position.y + 32, 100, 100 }, nullptr, { 255, 255, 255, 1 }, app->fonts->indicatorsFont);
	text->state = GuiControlState::DISABLED;

	return true;
}

bool Lever::CleanUp()
{
	app->colManager->world->DestroyBody(trigger->body);
	app->colManager->world->DestroyBody(collider->body);
	app->tex->UnLoad(texture);
	app->guiManager->DestroyGuiControl(text);

	return true;
}

void Lever::SetListener(Door* listener)
{
	this->listener = listener;
}

void Lever::SetQuest(uint32_t questID)
{
	this->questID = questID;
}

bool Lever::Update(float dt)
{

	return true;
}

void Lever::OnCollision(PhysBody* c1, PhysBody* c2)
{
	if (c2->eListener)
	{
		if (c2->eListener->type == EntityType::PLAYER)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
			{
				activated = !activated;
				app->questManager->UpdateQuest(questID);
				questID = 1000;
			}
		}
	}
}

bool Lever::Draw(Render* render)
{
	if (activated)
		render->DrawRectangle({ position.x - 16, position.y - 16, 32, 32 }, 0, 255, 255);
	else
		render->DrawRectangle({ position.x - 16, position.y - 16, 32, 32 }, 255, 0, 255);
	return true;
}



