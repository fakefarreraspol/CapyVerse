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

	texture = app->tex->Load("Assets/Textures/Sprites/characters.png");
	return true;
}

bool Enemy::Update(float dt)
{
	bool ret = true;
	return ret;
}

bool Enemy::Draw(Render* render)
{
	bool ret = true;
	if (!isCombat)
	{
		SDL_Rect rect = { 17, 132, 66, 66 };
		render->DrawTexture(texture, position.x - 32, position.y - 32, &rect);
	}
	return ret;
}

void Enemy::SetCombat(bool value)
{
	for (int i = 0; i < battleTeam.Count(); i++)
	{
		battleTeam.At(i)->data->SetCombat(value);
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
		if (c2->eListener->type == EntityType::PLAYER && !triggered && app->questManager->IsCompleated(0))
		{
			triggered = true;

			if (strcmp(this->NPCname.GetString(), "Evie"))
				app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene1, 2);
			if (strcmp(this->NPCname.GetString(), "Morgan"))
				app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene2, 2);
			if (strcmp(this->NPCname.GetString(), "Erin"))
				app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene3, 2);

		
		}
	}
}

bool Enemy::CleanUp()
{
	if(collider)
		app->colManager->world->DestroyBody(collider->body);
	
	if(trigger)
		app->colManager->world->DestroyBody(trigger->body);
	app->tex->UnLoad(texture);
	return true;
}
