#ifndef __EGIRLBARA_H__
#define __EGIRLBARA_H__

#include "Capybara.h"

class Egirlbara : public Capybara
{
public:
	Egirlbara(uint32 id, iPoint position);
	~Egirlbara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__EGIRLBARA_H__
