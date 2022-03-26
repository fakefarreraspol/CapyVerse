#ifndef __RAINBOWBARA_H__
#define __RAINBOWBARA_H__

#include "Capybara.h"

class Rainbowbara : public Capybara
{
public:
	Rainbowbara(uint32 id, iPoint position);
	~Rainbowbara();

	bool Update(float dt);

	void UseAbility(Capybara* target);

private:

};
#endif // !__RAINBOWBARA_H__
