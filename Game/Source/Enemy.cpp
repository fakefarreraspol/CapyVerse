#include "Enemy.h"

#include "Capybara.h"+

Enemy::Enemy(iPoint position, uint32 id, const char* name) : Entity(EntityType::ENEMY, id, name, position)
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
	return ret;
}

void Enemy::SetCombat(bool value)
{
	for (ListItem<Capybara*>* capy = battleTeam.start; capy != nullptr; capy = capy->next)
	{
		capy->data->SetCombat(value);
	}
}

List<Capybara*>& Enemy::GetBattleTeam()
{
	return battleTeam;
}

void Enemy::AddCapybaraToBatle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}
