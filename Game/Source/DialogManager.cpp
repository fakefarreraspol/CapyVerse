#include "DialogManager.h"

#include "App.h"
#include "Window.h"
#include "Render.h"
#include "GuiManager.h"
#include "DialogNode.h"

DialogManager::DialogManager(bool startEnabled):Module(startEnabled)
{
	name.Create("DialogManager");

}

DialogManager::~DialogManager()
{
	
}

bool DialogManager::Awake(pugi::xml_node&)
{


	return true;
}

bool DialogManager::Start()
{
	uint w, h;
	uint offset = 30;

	app->win->GetWindowSize(w, h);

	bounds.x = 200/2;
	bounds.y = h * 2 / 3;
	bounds.w = w-200;
	bounds.h = h - bounds.y;

	cBounds.x = bounds.x + offset;
	cBounds.y = bounds.y + offset;
	cBounds.w = 128;
	cBounds.h = 128;

	nBounds.x = cBounds.x;
	nBounds.y = cBounds.y + cBounds.h + (offset/2);
	nBounds.w = cBounds.w;
	nBounds.h = 40;

	tBounds.x = cBounds.x + cBounds.w + offset;
	tBounds.y = cBounds.y;
	tBounds.w = bounds.w - cBounds.w - 3*offset;
	tBounds.h = bounds.h - (2 * offset);

	bBounds.x = tBounds.x + tBounds.w - offset;
	bBounds.y = tBounds.y + tBounds.h - offset;
	bBounds.w = bBounds.h = offset;

	characterName = app->guiManager->CreateGuiControl(GuiControlType::TEXT, app->guiManager->controls.Count(), "Name", nBounds, this, { 255,255,255,255 });
	text = app->guiManager->CreateGuiControl(GuiControlType::TEXT, app->guiManager->controls.Count(), "example text hehe", tBounds, this, { 255,255,255,255 });
	button = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, app->guiManager->controls.Count(), "", bBounds, this, { 255,0,0,255 });

	return true;
}

bool DialogManager::Update(float dt)
{
	if (activeDialog != nullptr)
	{
		button->state = GuiControlState::NORMAL;
		characterName->state = GuiControlState::NORMAL;
		text->state = GuiControlState::NORMAL;


		


	}
	else
	{
		button->state = GuiControlState::DISABLED;
		characterName->state = GuiControlState::DISABLED;
		text->state = GuiControlState::DISABLED;
	}



	return true;
}

bool DialogManager::PostUpdate()
{
	// a hacer draw de las cositas
	// si hay tiempo pues hacer animaciones cuquis.
	if (activeDialog != nullptr)
	{
		app->render->DrawRectangle(bounds, 255, 255, 255, 255);
		app->render->DrawRectangle(cBounds, 0, 0, 0, 255);
		app->render->DrawRectangle(nBounds, 0, 0, 0, 255);
		app->render->DrawRectangle(tBounds, 0, 0, 0, 255);
	}

	

	
	//button->Draw(app->render);
	
	return true;
}

bool DialogManager::SetActiveDialog(Dialog* dialog)
{
	bool res = false;
	if (activeDialog == nullptr)
	{
		DialogNode* activeNode = activeDialog->GetActiveNode();

		if (dialog != nullptr)
		{
			activeDialog = dialog;
			
			
			// set character image
			// set character name
		}
		else
		{

			activeDialog = nullptr;

			
			
		}

		res = true;
	}
	return res;
}

bool DialogManager::OnGuiMouseClickEvent(GuiControl* control)
{
	DialogNode* activeNode = activeDialog->GetActiveNode();

	activeDialog->SetActiveNode(option);

	// delete the other options
	if (options.Count() != 0)
	{
		ListItem <GuiControl*>* item = options.start;

		while (item != nullptr)
		{
			app->guiManager->DestroyGuiControl(item->data);
			item = item->next;
		}
		options.Clear();
	}
	

	// creating options

	if (activeNode->nodes.Count() > 1)
	{
		button->state == GuiControlState::DISABLED;

		for (int i = 0; i < activeNode->nodes.Count(); i++)
		{
			SDL_Rect optionBounds = { 0,0,0,0 };
			int id = app->guiManager->controls.Count();
			GuiControl* newOption = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, activeNode->options.At(i)->data.GetString(), optionBounds, this, { 0,0,0,255 });
			options.Add(newOption);
		}

	}
	else
	{
		button->state == GuiControlState::NORMAL;
	}

	return true;
}
