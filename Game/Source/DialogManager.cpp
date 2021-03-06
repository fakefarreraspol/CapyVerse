#include "DialogManager.h"

#include "App.h"
#include "Scene.h"
#include "Window.h"
#include "Render.h"
#include "GuiManager.h"
#include "DialogNode.h"
#include "GuiText.h"
#include "Input.h"
#include "Textures.h"
#include "QuestManager.h"
#include "Player.h"

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

	bBounds.x = tBounds.x + tBounds.w - offset-50;
	bBounds.y = tBounds.y + tBounds.h - offset;
	bBounds.w = bBounds.h = offset;

	characterName = app->guiManager->CreateGuiControl(GuiControlType::TEXT, app->guiManager->controls.Count(), "Name", nBounds, this, { 255,255,255,255 });
	text = app->guiManager->CreateGuiControl(GuiControlType::TEXT, app->guiManager->controls.Count(), "example text hehe", tBounds, this, { 255,255,255,255 });
	button = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, app->guiManager->controls.Count(), "continue", bBounds, this, { 255,255,255,255 });
	button->state = GuiControlState::FOCUSED;

	// test dialog
	//app->scene->dialogTest = new Dialog();
	//DialogNode* first = new DialogNode("dialog test");
	//app->scene->dialogTest->AddFirstNode(first);

	//DialogNode* sec = app->scene->dialogTest->AddOption(first, "choose an option","");
	//app->scene->dialogTest->AddOption(sec, "you chose 4", "4");
	//app->scene->dialogTest->AddOption(sec, "you chose 3", "3");
	//app->scene->dialogTest->AddOption(sec, "you chose 2", "2");
	//app->scene->dialogTest->AddOption(sec, "you chose 1", "1");
	//app->dialogManager->SetActiveDialog(app->scene->dialogTest);
	texture = app->tex->Load("Assets/Menus/menus.png");

	return true;
}

bool DialogManager::Update(float dt)
{
	if (activeDialog != nullptr)
	{
		if (activeDialog->Finished() == true)
		{
			app->questManager->ActiveQuest(activeDialog->questID);
			activeDialog = nullptr;
		}
		else
		{
			if (activeDialog->GetActiveNode()->nodes.Count() > 1)
				button->state = GuiControlState::DISABLED;
			else
			{
				button->state = GuiControlState::FOCUSED;
			}
			characterName->state = GuiControlState::NORMAL;
			text->state = GuiControlState::NORMAL;

			if (optionButtons.Count() == 0)
			{
				button->state = GuiControlState::FOCUSED;
				button->Update(dt);
			}
			else
			{
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				{
					option++;
					if (option >= optionButtons.Count())
						option = 0;
				}
				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					option--;
					if (option < 0)
						option = optionButtons.Count()-1;
				}

				optionButtons.At(option)->data->state = GuiControlState::FOCUSED;
				ListItem <GuiControl*>* item = optionButtons.start;
				while (item != nullptr)
				{
					item->data->Update(dt);
					item = item->next;
				}
			}

		}
		
	}
	else
	{
		button->state = GuiControlState::DISABLED;
		characterName->state = GuiControlState::DISABLED;
		text->state = GuiControlState::DISABLED;
		app->scene->player->canMove = true;
	}



	return true;
}

bool DialogManager::PostUpdate()
{
	// a hacer draw de las cositas
	// si hay tiempo pues hacer animaciones cuquis.
	if (activeDialog != nullptr)
	{
		//app->render->DrawRectangle(bounds, 255, 255, 255, 255, true, false);
		//app->render->DrawRectangle(cBounds, 0, 0, 0, 255, true, false);
		//app->render->DrawRectangle(nBounds, 0, 0, 0, 255, true, false);
		//app->render->DrawRectangle(tBounds, 0, 0, 0, 255, true, false);
		SDL_Rect rect{ 0, 434, 1080, 241 };
		app->render->DrawTexture(texture, 100, 455, &rect, true);

		text->Draw(app->render);
		characterName->Draw(app->render);
		if (optionButtons.Count()==0)
			button->Draw(app->render);
		else
		{
			
			ListItem <GuiControl*>* item = optionButtons.start;
			while (item != nullptr)
			{
				item->data->Draw(app->render);
				item->data->state = GuiControlState::NORMAL;
				item = item->next;
			}

		}

	}
	//button->Draw(app->render);
	
	return true;
}

bool DialogManager::SetActiveDialog(Dialog* dialog)
{
	bool res = false;
	if (activeDialog == nullptr)
	{
		
		if (dialog != nullptr)
		{
			activeDialog = dialog;
			dialog->StartDialog();
			option = 0;

			DialogNode* activeNode = activeDialog->GetActiveNode();
			if (activeNode != nullptr)
			{
				text->SetText(activeNode->text.GetString());
			}
			app->scene->player->canMove = false;
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
	// delete the other options
	ListItem <GuiControl*>* item = optionButtons.start;

	while (item != nullptr)
	{
		app->guiManager->DestroyGuiControl(item->data);
		item = item->next;
	}
	optionButtons.Clear();

	// creating options

	activeDialog->SetActiveNode(option);
	DialogNode* activeNode = activeDialog->GetActiveNode();
	if (activeNode != nullptr)
		text->SetText(activeNode->text.GetString());

	if (activeNode->nodes.Count() > 1)
	{
		int offset = 20;

		for (int i = activeNode->nodes.Count()-1; i< 0; i--)
		{
			SDL_Rect optionBounds = { 0,0,0,0 };
			optionBounds.x = tBounds.x;
			optionBounds.y = tBounds.y + tBounds.h - offset*(i+1);
			optionBounds.w = tBounds.w / 2;
			optionBounds.h = offset;

			int id = app->guiManager->controls.Count();
			GuiControl* newOption = app->guiManager->CreateGuiControl(GuiControlType::BUTTON, id, activeNode->nodes.At(i)->data->optionText.GetString(), optionBounds, this, { 225,225,255,255 });
			newOption->state = GuiControlState::NORMAL;
			optionButtons.Add(newOption);
		}
		button->state = GuiControlState::DISABLED;
	}

	option = 0;

	return true;
}

bool DialogManager::CleanUp()
{
	app->tex->UnLoad(texture);
	optionButtons.Clear();
	return true;
}
