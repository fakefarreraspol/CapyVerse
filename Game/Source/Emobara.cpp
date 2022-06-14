#include "Emobara.h"

Emobara::Emobara(uint32 id, iPoint position) : Capybara(CapybaraType::DPS, id, position, "Emobara")
{
	this->capybaraStats.hp				= 1;
	this->capybaraStats.mp				= 1;
	this->capybaraStats.strenght		= 9;
	this->capybaraStats.speed			= 8;
	this->capybaraStats.intelligence	= 1;

	this->capybaraTarget = CapybaraTarget::HIMSELF;
	InitStats();
	idle.PushBack({ 64, 456, 60, 56 });
	currentAnim = &(idle);
}

Emobara::~Emobara()
{
}

bool Emobara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	SetStatus(CapybaraStatus::RAGE);
	this->mana -= 10;

	return true;
}
