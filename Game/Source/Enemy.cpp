#include "Enemy.h"

#include "App.h"
#include "Capybara.h"
#include "DialogManager.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "Textures.h"
#include "QuestManager.h"

Enemy::Enemy(iPoint position, uint32 id, const char* name) : NPC(position, id, name)
{
	normalEnemy.PushBack({ 17, 132, 32, 64 });
	boss.PushBack({ 152, 135, 28, 63 });

	
	currentAnim = &normalEnemy;
}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	collider->listener = (Module*)app->entMan;
	collider->eListener = this;

	trigger = app->colManager->CreateRectangleSensor(position.x, position.y, 128, 128, bodyType::STATIC);
	trigger->listener = (Module*)app->entMan;
	trigger->eListener = this;

	return true;
}

bool Enemy::Update(float dt)
{
	bool ret = true;
	
	if (isBoss && (currentAnim != &boss))
	{
		currentAnim = &boss;
	}
	return ret;
}
void Enemy::SetCombat(bool value)
{
	for (int i = 0; i < battleTeam.Count(); i++)
	{
		battleTeam.At(i)->data->SetCombat(value);
		battleTeam.At(i)->data->faceLeft = true;


		if (value)
			battleTeam.At(i)->data->Enable();
		else
			battleTeam.At(i)->data->Disable();
	}
	this->isCombat = value;
}

List<Capybara*>& Enemy::GetBattleTeam()
{
	return battleTeam;
}

void Enemy::AddCapybaraToBatle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}

void Enemy::OnCollision(PhysBody* c1, PhysBody* c2)
{
	if (c2->eListener)
	{
		if (c2->eListener->type == EntityType::PLAYER && !triggered)
		{
			
			if (app->questManager->IsCompleated(0))
			{
				app->dialogManager->SetActiveDialog(dialog);
				app->dialogManager->characterName->SetText(NPCname.GetString());
				if (dialog->Finished())
				{
					triggered = true;
					if (strcmp(this->NPCname.GetString(), "Evie"))
						app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene1, 2);
					if (strcmp(this->NPCname.GetString(), "Morgan"))
						app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene2, 2);
					if (strcmp(this->NPCname.GetString(), "Erin"))
						app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene3, 2);
					if (app->questManager->IsCompleated(1))
					{
						if (strcmp(this->NPCname.GetString(), "Mills"))
							app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene4, 2);
						if (strcmp(this->NPCname.GetString(), "George"))
							app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene5, 2);
						if (strcmp(this->NPCname.GetString(), "Darcy"))
							app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene6, 2);
						if (strcmp(this->NPCname.GetString(), "Hugh"))
							app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene7, 2);
					}
				}

			}
		
		}
	}
}

bool Enemy::CleanUp()
{
	if(collider)
		app->colManager->world->DestroyBody(collider->body);
	
	if(trigger)
		app->colManager->world->DestroyBody(trigger->body);
	return true;
}
