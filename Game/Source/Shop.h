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

	void Show();

	void UnShow();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

private:
	Inventory* shopInventory;

	GuiButton* buyBtn = nullptr;
	GuiButton* sellBtn = nullptr;
	GuiButton* returnBtn = nullptr;
	List<GuiButton*> itemsBtns;

	GuiText* playerMoneyTxt;
	int playerMoney;

	bool buy = true;
};
#endif // __Shop_H__

