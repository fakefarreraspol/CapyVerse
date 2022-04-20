#include "Chinabara.h"

Chinabara::Chinabara(uint32 id, iPoint position) : Capybara(CapybaraType::TANK, id, position, "Chinabara")
{
	this->capybaraStats.hp				= 6;
	this->capybaraStats.mp				= 3;
	this->capybaraStats.strenght		= 5;
	this->capybaraStats.speed			= 4;
	this->capybaraStats.intelligence	= 2;

	this->capybaraTarget = CapybaraTarget::ENEMIES;
	InitStats();
	anim.PushBack({ 63, 68, 61, 60 });
	currentAnim = &anim;
}

Chinabara::~Chinabara()
{
}

bool Chinabara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	target->SetStatus(CapybaraStatus::TAUNTED);
	this->mana -= 10;

	return true;
}
