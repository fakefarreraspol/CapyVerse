#include "NPC.h"

#include "App.h"
#include "Collider.h"
#include "Collisions.h"
#include "Dialog.h"
#include "Input.h"
#include "DialogManager.h"



#include "Scene.h"

NPC::NPC(iPoint position, uint32 id, const char* name) : Entity(EntityType::NPC, id, name, position)
{
	collider = app->colManager->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::NPC);
	dialog = nullptr;
}

NPC::~NPC()
{

}

bool NPC::Start()
{
	
	return true;
}

bool NPC::Update(float dt)
{
	/*if (app->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT)
		OnCollision(nullptr,nullptr);*/
	return true;
}

bool NPC::Draw(Render* render)
{
	render->DrawRectangle({ position.x,position.y,50,50 }, 228, 0, 224, 255);

	return true;
}

void NPC::OnCollision(Collider* c1, Collider* c2)
{
	app->dialogManager->SetActiveDialog(dialog);
	
}

bool NPC::CleanUp()
{
	app->colManager->RemoveCollider(collider);
	delete texture;
	delete dialog;

	return true;
}

bool NPC::LoadState(pugi::xml_node& node)
{
	position.x = node.child("position").attribute("x").as_float();
	position.y = node.child("position").attribute("y").as_float();

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