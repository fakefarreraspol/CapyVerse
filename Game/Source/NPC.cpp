#include "NPC.h"

#include "App.h"
#include "Dialog.h"
#include "Input.h"
#include "DialogManager.h"
#include "Textures.h"
#include "QuestManager.h"

#include "Physics.h"

#include "Scene.h"

NPC::NPC(iPoint position, uint32 id, const char* name) : Entity(EntityType::NPC, id, name, position)
{
	dialog = nullptr;
	NPCname.Create(name);
	idle.PushBack({ 83, 134, 32, 66 });
	currentAnim->SetAnim(idle);
	w = 32;
	h = 66;
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

void NPC::OnCollision(PhysBody* c1, PhysBody* c2)
{
	if (c2->eListener)
	{
		if (c2->eListener->type == EntityType::PLAYER && !dialog->Finished())
		{
			app->dialogManager->SetActiveDialog(dialog);
			app->dialogManager->characterName->SetText(NPCname.GetString());
		}
	}
}

bool NPC::CleanUp()
{
	if(collider)
		app->colManager->world->DestroyBody(collider->body);
	if(trigger)
		app->colManager->world->DestroyBody(trigger->body);

	return true;
}

bool NPC::LoadState(pugi::xml_node& node)
{
	/*position.x = node.child("position").attribute("x").as_int();
	position.y = node.child("position").attribute("y").as_int();
	collider->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0.0f);
	trigger->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0.0f);*/
	active = node.attribute("active").as_bool();
	renderable = node.attribute("renderable").as_bool();

	return true;
}
bool NPC::SaveState(pugi::xml_node& node)
{
	/*pugi::xml_node position = node.append_child("position");
	position.append_attribute("x").set_value(this->position.x);
	position.append_attribute("y").set_value(this->position.y);*/

	node.append_attribute("id").set_value(id);
	node.append_attribute("active").set_value(active);
	node.append_attribute("renderable").set_value(renderable);

	return true;
}