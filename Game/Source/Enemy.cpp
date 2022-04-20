#include "Enemy.h"

#include "App.h"
#include "Capybara.h"
#include "DialogManager.h"
#include "Collisions.h"
#include "Collider.h"
#include "FadeToBlack.h"

Enemy::Enemy(iPoint position, uint32 id, const char* name) : NPC(position, id, name)
{

}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	collider = app->colManager->AddCollider({ position.x - 32, position.y - 32, 128, 128 }, Collider::Type::ENEMY, (Module*)app->entMan, this);
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
		//if (app->GetDebug())
			render->DrawRectangle({ position.x, position.y,  64 , 64 }, 255, 0, 0);

		//render->DrawTexture(texture, position.x, position.y, &currentAnim->GetCurrentFrame());
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

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::PLAYER)
	{
		if (id == 10)
		{
			app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene1, 120);
		}
		if (id == 11)
		{
			app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene2, 120);
		}
		if (id == 12)
		{
			app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene3, 120);
		}
		app->colManager->RemoveCollider(collider);
	}

}

void Enemy::AddCapybaraToBatle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}

bool Enemy::CleanUp()
{
	app->colManager->RemoveCollider(collider);
	return true;
}
