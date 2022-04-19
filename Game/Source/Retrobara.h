#ifndef __RETROBARA_H__
#define __RETROBARA_H__

#include "Capybara.h"

class Retrobara : public Capybara
{
public:
	Retrobara(uint32 id, iPoint position);
	~Retrobara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__RETROBARA_H__
