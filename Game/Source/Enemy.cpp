#include "Enemy.h"

#include "App.h"
#include "Capybara.h"
#include "DialogManager.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "Textures.h"

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
	return true;
}

bool Enemy::Update(float dt)
{
	if (load)
	{
		texture = app->tex->Load("Assets/Textures/Sprites/characters.png");
		load = false;
	}
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
		if (c2->eListener->type == EntityType::PLAYER && !triggered)
		{
			triggered = true;

			if (this->id == 10)
				app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene1, 2);
			if (this->id == 11)
				app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene2, 2);
			if (this->id == 12)
				app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene3, 2);

		
		}
	}
}

bool Enemy::CleanUp()
{
	
	return true;
}
