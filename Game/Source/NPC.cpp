#include "NPC.h"

#include "App.h"
#include "Dialog.h"
#include "Input.h"
#include "DialogManager.h"
#include "Textures.h"

#include "Physics.h"

#include "Scene.h"

NPC::NPC(iPoint position, uint32 id, const char* name) : Entity(EntityType::NPC, id, name, position)
{
	dialog = nullptr;
}

NPC::~NPC()
{

}

bool NPC::Start()
{
	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	collider->listener = (Module*)app->entMan;
	collider->eListener = this;

	trigger = app->colManager->CreateRectangleSensor(position.x, position.y, 128, 128, bodyType::STATIC);
	trigger->listener = (Module*)app->entMan;
	trigger->eListener = this;
	return true;
}

bool NPC::Update(float dt)
{
	if (load)
	{
		texture = app->tex->Load("Assets/Textures/Sprites/characters.png");
		load = false;
	}
	
	if (dialog->Finished() && triggerCounter >= 0)
	{
		triggerCounter--;
		if (triggerCounter == 0)
		{
			triggerCounter = 120;
			dialog->finished = false;
		}
	}

	return true;
}

bool NPC::Draw(Render* render)
{
	SDL_Rect rect = { 17, 198, 66, 66 };
	render->DrawTexture(texture, position.x - 32, position.y - 32, &rect);

	return true;
}

void NPC::OnCollision(PhysBody* c1, PhysBody* c2)
{
	if (c2->eListener)
	{
		if (c2->eListener->type == EntityType::PLAYER && !dialog->Finished())
		{
			app->dialogManager->SetActiveDialog(dialog);
			app->dialogManager->characterName->SetText(this->name.GetString());
		}
	}
}

bool NPC::CleanUp()
{
	return true;
}

bool NPC::LoadState(pugi::xml_node& node)
{
	position.x = node.child("position").attribute("x").as_int();
	position.y = node.child("position").attribute("y").as_int();

	active = node.attribute("active").as_bool();
	renderable = node.attribute("renderable").as_bool();

	return true;
}
bool NPC::SaveState(pugi::xml_node& node)
{
	pugi::xml_node position = node.append_child("position");
	position.append_attribute("x").set_value(this->position.x);
	position.append_attribute("y").set_value(this->position.y);

	node.append_attribute("id").set_value(id);
	node.append_attribute("active").set_value(active);
	node.append_attribute("renderable").set_value(renderable);

	return true;
}