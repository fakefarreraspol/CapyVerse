#include "Rainbowbara.h"

Rainbowbara::Rainbowbara(uint32 id, iPoint position) : Capybara(CapybaraType::SUPP, id, position, "Rainbowbara")
{
	this->capybaraStats.hp				= 3;
	this->capybaraStats.mp				= 5;
	this->capybaraStats.strenght		= 2;
	this->capybaraStats.speed			= 4;
	this->capybaraStats.intelligence	= 6;

	InitStats();
}

Rainbowbara::~Rainbowbara()
{
}

bool Rainbowbara::Update(float dt)
{
	return true;
}

void Rainbowbara::UseAbility(Capybara* target)
{
}
