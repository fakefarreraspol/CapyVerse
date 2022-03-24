#ifndef __CHINABARA_H__
#define __CHINABARA_H__

#include "Capybara.h"

class Chinabrara : public Capybara
{
public:
	Chinabrara(uint32 id, iPoint position);
	~Chinabrara();

	bool Update(float dt);

	void UseAbility(Capybara* target);

private:

};


#endif // !__CHINABARA_H__

