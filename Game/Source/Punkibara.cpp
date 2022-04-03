#include "Punkibara.h"

Punkibara::Punkibara(uint32 id, iPoint position) : Capybara(CapybaraType::DPS, id, position, "Punkibara")
{
	this->capybaraStats.hp				= 3;
	this->capybaraStats.mp				= 2;
	this->capybaraStats.strenght		= 7;
	this->capybaraStats.speed			= 6;
	this->capybaraStats.intelligence	= 2;

	InitStats();
}

Punkibara::~Punkibara()
{
}


bool Punkibara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;
	this->capybaraStatus = CapybaraStatus::RAGE;
	this->mana -= 10;

	return true;
}
