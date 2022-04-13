#include "Egirlbara.h"

Egirlbara::Egirlbara(uint32 id, iPoint position) : Capybara(CapybaraType::DPS, id, position, "Egirlbara")
{
	this->capybaraStats.hp				= 3;
	this->capybaraStats.mp				= 1;
	this->capybaraStats.strenght		= 7;
	this->capybaraStats.speed			= 8;
	this->capybaraStats.intelligence	= 1;

	this->capybaraTarget = CapybaraTarget::HIMSELF;
	InitStats();
}

Egirlbara::~Egirlbara()
{
}

bool Egirlbara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	SetStatus(CapybaraStatus::RAGE);
	this->mana -= 10;

	return true;
}