#include "Lever.h"
#include "App.h"
#include "Input.h"
#include "Physics.h"
#include "GuiManager.h"
#include "Fonts.h"
#include "QuestManager.h"
#include "Textures.h"
#include "Bridge.h"

Lever::Lever(iPoint position, uint32_t id, uint32_t questID) : Entity(EntityType::LEVER, id, "Lever", position), questID(questID)
{
	trigger = app->colManager->CreateRectangleSensor(position.x, position.y, 64, 64, bodyType::STATIC);
	trigger->eListener = this;
	trigger->listener = (Module*)app->entMan;
	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	text = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "Press E to switch", { position.x - 50, position.y + 32, 100, 100 }, nullptr, { 255, 255, 255, 1 }, app->fonts->indicatorsFont);
	text->state = GuiControlState::DISABLED;
	texture = app->tex->Load("Assets/Textures/Sprites/props.png");

	open.PushBack({ 6, 146, 24,32 });
	closed.PushBack({ 34, 146, 24,32 });

	anim = &open;
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
	if (!collider)
	{
		collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	}
	if(!text)
		text = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "Press E to switch", { position.x - 50, position.y + 32, 100, 100 }, nullptr, { 255, 255, 255, 1 }, app->fonts->indicatorsFont);
	text->state = GuiControlState::DISABLED;
	texture = app->tex->Load("Assets/Textures/Sprites/props.png");
	return true;
}

bool Lever::CleanUp()
{
	if(trigger)
		app->colManager->world->DestroyBody(trigger->body);
	if(collider)
		app->colManager->world->DestroyBody(collider->body);
	app->tex->UnLoad(texture);
	app->guiManager->DestroyGuiControl(text);

	return true;
}

void Lever::SetListener(Bridge* listener)
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
		if (c2->eListener->type == EntityType::PLAYER && !activated)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
			{
				activated = true;
				app->questManager->UpdateQuest(questID);
				if(listener)
					listener->Update();
			}
		}
	}
}

bool Lever::Draw(Render* render)
{
	if (activated)
		render->DrawTexture(texture, position.x - 16, position.y - 16, &closed.GetCurrentFrame());
	else
		render->DrawTexture(texture, position.x - 16, position.y - 16, &open.GetCurrentFrame());
	return true;
}



