#include "Chinabara.h"

Chinabara::Chinabara(uint32 id, iPoint position) : Capybara(CapybaraType::TANK, id, position, "Chinabara")
{
	this->capybaraStats.hp				= 6;
	this->capybaraStats.mp				= 3;
	this->capybaraStats.strenght		= 5;
	this->capybaraStats.speed			= 4;
	this->capybaraStats.intelligence	= 2;

	InitStats();
}

Chinabara::~Chinabara()
{
}

void Chinabara::UseAbility(Capybara* target)
{

}
