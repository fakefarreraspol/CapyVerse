#ifndef __EMOBARA_H__
#define __EMOBARA_H__

#include "Capybara.h"

class Emobara : public Capybara
{
public:
	Emobara(uint32 id, iPoint position);
	~Emobara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__EMOBARA_H__
