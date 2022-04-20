#include "Enemy.h"

#include "App.h"
#include "Capybara.h"
#include "DialogManager.h"

Enemy::Enemy(iPoint position, uint32 id, const char* name) : NPC(position, id, name)
{

}

Enemy::~Enemy()
{
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
		if (app->GetDebug())
			render->DrawRectangle({ position.x, position.y,  20 , 20 }, 255, 255, 0);

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
	app->dialogManager->SetActiveDialog(dialog);
}

void Enemy::AddCapybaraToBatle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}
