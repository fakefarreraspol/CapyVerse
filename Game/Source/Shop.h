#ifndef __SHOP_H__
#define __SHOP_H__

#include "Module.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "GuiText.h"
#include "Inventory.h"
#include "List.h"


struct SDL_Texture;

class Shop : public Module
{
public:

	Shop(bool startEnabled);

	// Destructor
	virtual ~Shop();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	Inventory* shopInventory;




};
#endif // __Shop_H__

