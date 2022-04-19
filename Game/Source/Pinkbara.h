#ifndef __PINKBARA_H__
#define __PINKBARA_H__

#include "Capybara.h"

class Pinkbara : public Capybara
{
public:
	Pinkbara(uint32 id, iPoint position);
	~Pinkbara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__PINKBARA_H__

