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

bool Punkibara::Update(float dt)
{
	return true;
}

void Punkibara::UseAbility(Capybara* target)
{
}
