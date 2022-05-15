#include "Punkibara.h"

Punkibara::Punkibara(uint32 id, iPoint position) : Capybara(CapybaraType::DPS, id, position, "Punkibara")
{
	this->capybaraStats.hp				= 3;
	this->capybaraStats.mp				= 2;
	this->capybaraStats.strenght		= 7;
	this->capybaraStats.speed			= 6;
	this->capybaraStats.intelligence	= 2;
	this->capybaraTarget = CapybaraTarget::HIMSELF;
	InitStats();
	anim.PushBack({ 64, 192, 60, 62 });
	anim.PushBack({ 0, 192, 60, 62 });
	currentAnim = &anim;
}

Punkibara::~Punkibara()
{
}


bool Punkibara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;
	SetStatus(CapybaraStatus::RAGE);
	this->mana -= 10;

	return true;
}
