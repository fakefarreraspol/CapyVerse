#ifndef __CHADBARA_H__
#define __CHADBARA_H__

#include "Capybara.h"

class Chadbara : public Capybara
{
public:
	Chadbara(uint32 id, iPoint position);
	~Chadbara();

	bool UseAbility(Capybara* target);

private:

};


#endif // !__CHADBARA_H__
