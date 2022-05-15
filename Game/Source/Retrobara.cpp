#include "Retrobara.h"

Retrobara::Retrobara(uint32 id, iPoint position) : Capybara(CapybaraType::TANK, id, position, "Retrobara")
{
	this->capybaraStats.hp				= 7;
	this->capybaraStats.mp				= 2;
	this->capybaraStats.strenght		= 4;
	this->capybaraStats.speed			= 3;
	this->capybaraStats.intelligence	= 4;

	this->capybaraTarget = CapybaraTarget::ENEMIES;
	InitStats();
	anim.PushBack({ 64, 392, 60, 56 });
	anim.PushBack({ 0, 392, 60, 56 });
	currentAnim = &anim;
}

Retrobara::~Retrobara()
{
}

bool Retrobara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	SetStatus(CapybaraStatus::DEFENSIVE);
	this->mana -= 10;

	return true;
}
