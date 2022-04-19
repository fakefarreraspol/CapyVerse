#ifndef __SIMPBARA_H__
#define __SIMPBARA_H__

#include "Capybara.h"

class Simpbara : public Capybara
{
public:
	Simpbara(uint32 id, iPoint position);
	~Simpbara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__SIMPBARA_H__
