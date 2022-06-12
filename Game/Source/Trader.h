#ifndef __TRADER_H__
#define __TRADER_H__

#include "NPC.h"

#include "List.h"
#include "Animation.h"
#include "Dialog.h"

class Capybara;

class Trader : public NPC
{
public:
	Trader(iPoint position, uint32 id, const char* name);
	~Trader();
	bool Start();
	//Base functions
	bool Update(float dt);

	bool CleanUp();
private:

};


#endif // !__Trader_H__

