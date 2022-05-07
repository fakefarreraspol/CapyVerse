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
	collider = app->colManager->CreateRectangleSensor(position.x, position.y, 128, 128, bodyType::DYNAMIC);
	collider->listener = (Module*)app->entMan;
	collider->eListener = this;
	return true;
}

bool NPC::Update(float dt)
{
	if (load)
	{
		texture = app->tex->Load("Assets/Textures/Sprites/characters.png");
		load = false;
	}
	/*if (app->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT)
		OnCollision(nullptr,nullptr);*/
	return true;
}

bool NPC::Draw(Render* render)
{
	if (app->GetDebug())
		render->DrawRectangle({ position.x, position.y,  64 , 64 }, 255, 0, 0);
	SDL_Rect rect = { 17, 198, 66, 66 };
	render->DrawTexture(texture, position.x, position.y, &rect);

	return true;
}

void NPC::OnCollision(PhysBody* c1, PhysBody* c2)
{

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