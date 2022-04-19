#include "Chadbara.h"

Chadbara::Chadbara(uint32 id, iPoint position) : Capybara(CapybaraType::TANK, id, position, "Chadbara")
{
	this->capybaraStats.hp				= 9;
	this->capybaraStats.mp				= 1;
	this->capybaraStats.strenght		= 7;
	this->capybaraStats.speed			= 2;
	this->capybaraStats.intelligence	= 1;

	this->capybaraTarget = CapybaraTarget::ENEMIES;
	InitStats();
}

Chadbara::~Chadbara()
{
}

bool Chadbara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	target->SetStatus(CapybaraStatus::BLEED);
	this->mana -= 10;

	return true;
}