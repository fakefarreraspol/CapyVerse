#ifndef __MODULE_H__
#define __MODULE_H__

#include "PugiXml/src/pugixml.hpp"
#include "Optick/include/optick.h"

#include "SString.h"

class App;

class Module
{
public:

	Module() : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	// L01: DONE 5: Sending config file to all modules
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}
	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&) const
	{
		return true;
	}
	virtual void Enable()
	{
		if (!isEnabled)
		{
			isEnabled = true;
			Start();
		}
	}

	virtual void Disable()
	{
		if (isEnabled)
		{
			isEnabled = false;
			CleanUp();
		}
	}
	bool IsEnabled() const
	{
		return isEnabled;
	}
public:

	SString name;
	bool active;
	bool isEnabled = true;
};

#endif // __MODULE_H__