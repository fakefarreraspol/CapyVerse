#ifndef __CHINABARA_H__
#define __CHINABARA_H__

#include "Capybara.h"

class Chinabara : public Capybara
{
public:
	Chinabara(uint32 id, iPoint position);
	~Chinabara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__CHINABARA_H__

