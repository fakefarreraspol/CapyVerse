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

	// test dialog
	dialog = new Dialog();
	DialogNode* first = new DialogNode("dialog NPC");
	dialog->AddFirstNode(first);

	DialogNode* sec = dialog->AddOption(first, "choose an option", "");
	dialog->AddOption(sec, "you chose 4", "4");
	dialog->AddOption(sec, "you chose 3", "3");
	dialog->AddOption(sec, "you chose 2", "2");
	dialog->AddOption(sec, "you chose 1", "1");



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
	// start dialog if player interacts
	// select dialog depending on quest manager

	/*if (c2->type == Collider::Type::PLAYER)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
			if (dialog != nullptr)
				app->dialogManager->SetActiveDialog(this->dialog);
	}*/

	app->dialogManager->SetActiveDialog(dialog);
	//app->dialogManager->SetActiveDialog(app->scene->dialogTest);
}

bool NPC::CleanUp()
{
	app->colManager->RemoveCollider(collider);
	delete texture;
	delete dialog;

	return true;
}