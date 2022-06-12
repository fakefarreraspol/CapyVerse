#include "Trader.h"

#include "App.h"
#include "Capybara.h"
#include "DialogManager.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "Textures.h"
#include "QuestManager.h"

Trader::Trader(iPoint position, uint32 id, const char* name) : NPC(position, id, name)
{

}

Trader::~Trader()
{
}

bool Trader::Start()
{
	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	collider->listener = (Module*)app->entMan;
	collider->eListener = this;

	trigger = app->colManager->CreateRectangleSensor(position.x, position.y, 128, 128, bodyType::STATIC);
	trigger->listener = (Module*)app->entMan;
	trigger->eListener = this;

	return true;
}

bool Trader::Update(float dt)
{
	bool ret = true;

	return ret;
}

bool Trader::CleanUp()
{
	if (collider)
		app->colManager->world->DestroyBody(collider->body);

	if (trigger)
		app->colManager->world->DestroyBody(trigger->body);
	return true;
}