#include "Pinkbara.h"

Pinkbara::Pinkbara(uint32 id, iPoint position) : Capybara(CapybaraType::SUPP, id, position, "Pinkbara")
{
	this->capybaraStats.hp				= 3;
	this->capybaraStats.mp				= 6;
	this->capybaraStats.strenght		= 1;
	this->capybaraStats.speed			= 5;
	this->capybaraStats.intelligence	= 7;

	this->capybaraTarget = CapybaraTarget::ALLIES;
	InitStats();
	anim.PushBack({ 64, 264, 60, 56 });
	anim.PushBack({ 0, 264, 60, 56 });
	currentAnim = &anim;
}

Pinkbara::~Pinkbara()
{
}

bool Pinkbara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	target->SetStatus(CapybaraStatus::CLEVER);
	this->mana -= 10;

	return true;
}