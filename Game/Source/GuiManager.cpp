#include "GuiManager.h"


#include "GuiManager.h"
#include "App.h"
#include "Textures.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "GuiText.h"
#include "GuiBar.h"

#include "StatsMenu.h"

#include "Audio.h"

GuiManager::GuiManager(bool startEnabled) :Module(startEnabled)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{
	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, SDL_Color textColor, int fontID, bool blink)
{
	// L14: TODO1: Create a GUI control and add it to the list of controls

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:	control = new GuiButton(id, bounds, text, textColor, fontID);		break;
	case GuiControlType::SLIDER:	control = new GuiSlider(id, bounds, text);		break;
	case GuiControlType::CHECKBOX:	control = new GuiCheckBox(id, bounds, text);	break;
	case GuiControlType::TEXT:		control = new GuiText(id, bounds, text, textColor, fontID, blink);		break;
	case GuiControlType::BAR:		control = new GuiBar(id, bounds, text);		break;
		// More Gui Controls can go here

	default:
		break;
	}

	//Set the observer
	control->SetObserver(observer);
	//control->SetTexture(texture);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.Add(control);

	return control;
}

void GuiManager::DestroyGuiControl(GuiControl* entity)
{
	ListItem<GuiControl*>* item;

	for (item = controls.start; item != nullptr; item = item->next)
	{
		if (item->data == entity)
		{
			controls.Del(item);
			break;
		}

	}

	return;
}

bool GuiManager::Update(float dt)
{
	bool ret = true;
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	ret = UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}


	return ret;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {
	bool ret = true;
	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr && ret)
		{
			/*if (activeControl == nullptr)
				ret = control->data->Update(dt);
			else if (activeControl == control->data)*/
			ret = control->data->Update(dt);
			control = control->next;
		}

	}
	return ret;
}

bool GuiManager::PostUpdate()
{

	return Draw();
}

bool GuiManager::Draw() {

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	return true;

}

bool GuiManager::SetActiveControll(GuiControl* active)
{
	if (activeControl == nullptr)
		activeControl = active;
	else if (active == nullptr)
		activeControl = nullptr;

	return true;
}

const GuiControl* GuiManager::GetActiveControll()
{
	return activeControl;
}

bool GuiManager::CleanUp()
{
	controls.Clear();

	return true;
}


