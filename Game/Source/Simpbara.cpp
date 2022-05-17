#include "Simpbara.h"

Simpbara::Simpbara(uint32 id, iPoint position) : Capybara(CapybaraType::SUPP, id, position, "Simpbara")
{
	this->capybaraStats.hp				= 2;
	this->capybaraStats.mp				= 5;
	this->capybaraStats.strenght		= 1;
	this->capybaraStats.speed			= 5;
	this->capybaraStats.intelligence	= 7;

	this->capybaraTarget = CapybaraTarget::ALLIES;
	InitStats();
	idle.PushBack({ 64, 517, 60, 59 });
	currentAnim->SetAnim(idle);
}

Simpbara::~Simpbara()
{
}

bool Simpbara::UseAbility(Capybara* target)
{
	if (this->mana < 10)
		return false;

	target->SetStatus(CapybaraStatus::CLEVER);
	this->mana -= 10;

	return true;
}