#include "Rainbowbara.h"

Rainbowbara::Rainbowbara(uint32 id, iPoint position) : Capybara(CapybaraType::SUPP, id, position, "Rainbowbara")
{
	this->capybaraStats.hp				= 3;
	this->capybaraStats.mp				= 5;
	this->capybaraStats.strenght		= 2;
	this->capybaraStats.speed			= 4;
	this->capybaraStats.intelligence	= 6;
	this->capybaraTarget = CapybaraTarget::ALLIES;
	InitStats();
	anim.PushBack({ 64, 136, 60, 56 });
	currentAnim = &anim;
}

Rainbowbara::~Rainbowbara()
{
}

bool Rainbowbara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	target->Heal(this->capybaraStats.intelligence * 2);
	this->mana -= 10;

	return true;
}
