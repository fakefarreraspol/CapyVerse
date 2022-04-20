#include "Pause.h"

#include "App.h"
#include "GuiManager.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"

#include "Log.h"

Pause::Pause(bool startEnabled) : Module(startEnabled)
{
	name.Create("pause");
}

// Destructor
Pause::~Pause()
{}

// Called before render is available
bool Pause::Awake(pugi::xml_node& node)
{
	LOG("Loading Pause");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool Pause::Start()
{
	app->guiManager->Enable();

	pauseText = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 0, "PAUSE",{585, 235, 125, 25}, this, {255, 255, 255});
	pauseText->state = GuiControlState::DISABLED;
	menuBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "CONTINUE",{585, 290, 125, 25}, this, {255, 255, 255}));
	optionsBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "OPTIONS", { 585, 345, 125, 20 }, this, { 255, 255, 255 });
	menuBtns.Add(optionsBtn);
	menuBtns.Add((GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "SAVE", { 585, 400, 125, 25 }, this, { 255, 255, 255 }));
	exitBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "EXIT GAME", { 585, 460, 125, 20 }, this, { 255, 255, 255 });
	menuBtns.Add(exitBtn);

	

	for (int i = 0; i < menuBtns.Count(); i++)
	{
		menuBtns.At(i)->data->state = GuiControlState::DISABLED;
	}

	


	
	volumeBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "VOLUME", { 325, 285, 125, 20 }, this, { 255, 255, 255 });

	musicSldr = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 9, "MUSIC", { 500, 280, 220, 20 }, this);
	musicSldr->SetValues(100, 1, 50);
	soundSlrd = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 10, "SOUND FX", { 500, 320, 220, 20 }, this);
	soundSlrd->SetValues(100, 1, 50);
	fullscreenChkbx = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 11, "FULLSCREEN", { 325, 375, 25, 25 }, this);
	vsyncChkbx = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 12, "VSYNC            ", { 325, 420, 25, 25 }, this);
	returnOPBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "RETURN", { 325, 485, 125, 20 }, this, { 255, 255, 255 });

	optionsBtns.Add(volumeBtn);
	optionsBtns.Add(musicSldr);
	optionsBtns.Add(soundSlrd);
	optionsBtns.Add(fullscreenChkbx);
	optionsBtns.Add(vsyncChkbx);
	optionsBtns.Add(returnOPBtn);

	noBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "NO", { 565, 380, 25, 20 }, this, { 255, 255, 255, 1 });
	yesBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "YES", { 750, 380, 25, 20 }, this, { 255, 255, 255, 1 });
	exitText = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 200, "ARE YOU SURE YOU WANT TO EXIT THE GAME?", { 475, 325, 420, 15 }, this, { 255, 255, 255, 1 });

	exitBtns.Add(noBtn);
	exitBtns.Add(yesBtn);


	volumeBtn->state = GuiControlState::DISABLED;
	musicSldr->state = GuiControlState::DISABLED;
	soundSlrd->state = GuiControlState::DISABLED;
	fullscreenChkbx->state = GuiControlState::DISABLED;
	vsyncChkbx->state = GuiControlState::DISABLED;
	returnOPBtn->state = GuiControlState::DISABLED;

	yesBtn->state = GuiControlState::DISABLED;
	noBtn->state = GuiControlState::DISABLED;
	exitText->state = GuiControlState::DISABLED;

	arrow = app->tex->Load("Assets/Menus/arrow.png");
	currentControls = menuBtns;
	currentControl = currentControls.start;

	return true;
}

// Called each loop iteration
bool Pause::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Pause::Update(float dt)
{
	if (app->pause)
	{
		vsyncChkbx->checked = app->render->vsync;
		fullscreenChkbx->checked = app->win->fullscreen;

		app->audio->volFX = soundSlrd->value;
		app->audio->volMusic = musicSldr->value;
		GamePad& pad = app->input->pads[0];
		if (yesBtn->state == GuiControlState::DISABLED)
		{
			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || pad.down)
			{

				if (currentControl->next == nullptr)
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControls.start;
				}
				else
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControl->next;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || pad.up)
			{
				if (currentControl->prev == nullptr)
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControls.end;
				}
				else
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControl->prev;
				}
			}
		}
		else
		{
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || pad.down)
			{

				if (currentControl->next == nullptr)
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControls.start;
				}
				else
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControl->next;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || pad.up)
			{
				if (currentControl->prev == nullptr)
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControls.end;
				}
				else
				{
					currentControl->data->state = GuiControlState::NORMAL;
					currentControl = currentControl->prev;
				}
			}
		}
		currentControl->data->state = GuiControlState::FOCUSED;
		app->render->DrawRectangle({ 540, 210, 195, 300 }, 170, 170, 170, 120);
		app->render->DrawTexture(arrow, currentControl->data->bounds.x - 30, currentControl->data->bounds.y - 3);
	}
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		app->pause = !app->pause;
		for (int i = 0; i < menuBtns.Count(); i++)
		{
			
			menuBtns.At(i)->data->state = GuiControlState::NORMAL;
			pauseText->state = GuiControlState::NORMAL;
			currentControl = currentControls.start;
		}
		app->audio->volFX = 10;
		app->audio->volMusic = 10;
	}
	

	return true;
}

// Called each loop iteration
bool Pause::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool Pause::CleanUp()
{
	LOG("Freeing scene");
	app->guiManager->Disable();

	app->tex->UnLoad(arrow);
	menuBtns.Clear();
	optionsBtns.Clear();
	exitBtns.Clear();


	return true;
}

bool Pause::OnGuiMouseClickEvent(GuiControl* control)
{
	bool ret = true;
	if (control->id == 1)
	{
		//CONTINUES
		app->pause = false;
		for (int i = 0; i < menuBtns.Count(); i++)
		{
			menuBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		pauseText->state = GuiControlState::DISABLED;
	}
	if (control->id == 2)
	{
		//OPTIONS
		for (int i = 0; i < optionsBtns.Count(); i++)
		{
			optionsBtns.At(i)->data->state = GuiControlState::NORMAL;
		}
		for (int i = 0; i < menuBtns.Count(); i++)
		{
			menuBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		pauseText->state = GuiControlState::DISABLED;
		currentControls = optionsBtns;
		currentControl = currentControls.start;
	}
	if (control->id == 3)
	{
		//SAVE
		app->SaveGameRequest();
	}
	if (control->id == 4)
	{
		//EXIT
		for (int i = 0; i < exitBtns.Count(); i++)
		{
			exitBtns.At(i)->data->state = GuiControlState::NORMAL;
		}
		exitText->state = GuiControlState::NORMAL;
		currentControls = exitBtns;
		currentControl = currentControls.start;
	}
	if (control->id == 8)
	{
		//VOLUME
	}
	if (control->id == 9)
	{
		//MUSIC
	}
	if (control->id == 10)
	{
		//SOUND FX
	}
	if (control->id == 11)
	{
		//FULLSCREEN
		app->win->SetFullscreen(fullscreenChkbx->checked);
		app->render->SetFullScreen();

	}
	if (control->id == 12)
	{
		//VSYNC
		app->render->vsync = !app->render->vsync;
		app->render->SetVsync(app->render->vsync, (Module*)this);
	}
	if (control->id == 13)
	{
		//RETURN
		for (int i = 0; i < optionsBtns.Count(); i++)
		{
			optionsBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		currentControl = menuBtns.At(1);
		currentControls = menuBtns;
	}
	if (control->id == 14)
	{
		//NO
		for (int i = 0; i < exitBtns.Count(); i++)
		{
			exitBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		exitText->state = GuiControlState::DISABLED;
		currentControls = menuBtns;
		currentControl = menuBtns.At(3);
	}
	if (control->id == 15)
	{
		//YES
		ret = false;
	}
	return ret;
}
