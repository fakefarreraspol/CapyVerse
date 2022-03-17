#include "Capybara.h"

Capybara::Capybara(CapybaraType capyType, iPoint pos) : Entity(EntityType::CAPYBARA), capybaraType(capyType)
{
	position.x = pos.x;
	position.y = pos.y;
}

Capybara::~Capybara()
{
}

bool Capybara::Update(float dt)
{
	bool ret = true;

	return ret;
}

bool Capybara::Draw(Render* render)
{
	bool ret = true;

	render->DrawRectangle({position.x, position.y, 10, 10}, 255, 0, 0);
	return ret;
}

int Capybara::GetHealth()
{
	return health;
}

int Capybara::GetMana()
{
	return mana;
}

CapybaraType Capybara::GetType()
{
	return capybaraType;
}

CapybaraStats Capybara::GetStats()
{
	return capybaraStats;
}

void Capybara::Damage(int damage)
{

}

void Capybara::Heal(int heal)
{
	if (heal + health < maxHealth)
	{
		health += heal;
		return;
	}

	health = maxHealth;

	return;
}

void Capybara::UseAbility()
{

}

void Capybara::Attack(Capybara* target)
{
	
}

void Capybara::LevelUp()
{
	
	switch (capybaraType)
	{
	//Each capybara levels up 1 point per level or 2 depending on their type
	case CapybaraType::NONE:
	{
		capybaraStats.hp++;
		capybaraStats.mp++;
		capybaraStats.strenght++;
		capybaraStats.speed++;
		capybaraStats.armor++;
		capybaraStats.intelligence++;
	}break;
	//Tank levels up 2 points on hp and armor
	case CapybaraType::TANK:
	{
		capybaraStats.hp += 2;
		capybaraStats.mp++;
		capybaraStats.strenght++;
		capybaraStats.speed++;
		capybaraStats.armor += 2;
		capybaraStats.intelligence++;
	}break;
	//DPS levels up 2 points on speed and strength
	case CapybaraType::DPS:
	{
		capybaraStats.hp++;
		capybaraStats.mp++;
		capybaraStats.strenght += 2;
		capybaraStats.speed += 2;
		capybaraStats.armor++;
		capybaraStats.intelligence++;
	}break;
	//Supp levels up 2 points on mp and intelligence
	case CapybaraType::SUPP:
	{
		capybaraStats.hp++;
		capybaraStats.mp += 2;
		capybaraStats.strenght++;
		capybaraStats.speed++;
		capybaraStats.armor++;
		capybaraStats.intelligence += 2;
	}break;
	default: 
		break;
	}

	return;
}

void Capybara::UpdateStats()
{
	maxHealth = capybaraStats.hp * healthXLvl;
	maxMana = capybaraStats.mp * manaXLvl;
	damage = capybaraStats.strenght * damageXLvl;
}
