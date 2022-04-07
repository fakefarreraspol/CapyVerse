#ifndef __DIALOG_MANAGER_H__
#define __DIALOG_MANAGER_H__

#pragma once
#include "Module.h"

#include "Dialog.h"
#include "GuiControl.h"

class DialogManager : public Module
{
public:
	DialogManager(bool startEnabled);
	~DialogManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();

	bool SetActiveDialog(Dialog* dialog);
	bool OnGuiMouseClickEvent(GuiControl* control);

private:

	Dialog* activeDialog = nullptr;
	int option;
	SDL_Rect bounds, cBounds, nBounds, tBounds, bBounds;
	GuiControl* characterName;
	GuiControl* text;
	GuiControl* button;

	List<GuiControl*> options;


};

#endif // !__DIALOG_MANAGER_H__
