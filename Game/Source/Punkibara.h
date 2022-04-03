#ifndef __PUNKIBARA_H__
#define __PUNKIBARA_H__

#include "Capybara.h"

class Punkibara : public Capybara
{
public:
	Punkibara(uint32 id, iPoint position);
	~Punkibara();



	bool UseAbility(Capybara* target);

private:

};


#endif // !__PUNKIBARA_H__
