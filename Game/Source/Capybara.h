#ifndef __CAPYBARA_H__
#define __CAPYBARA_H__

#include "Entity.h"

struct CapybaraStats
{
	int hp;
	int mp;
	int strenght;
	int armor;
	int intelligence;
};


class Capybara : public Entity
{
public:
	Capybara();
	~Capybara();

private:
	CapybaraStats capybaraStats;

};

#endif // !__CAPYBARA_H__
