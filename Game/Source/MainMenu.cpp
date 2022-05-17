#include "MainMenu.h"

#include "App.h"
#include "FadeToBlack.h"
#include "GuiManager.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"
#include "Scene.h"
#include "Pause.h"
#include "easings.h"
#include "Log.h"

MainMenu::MainMenu(bool startEnabled) : Module(startEnabled)
{
	name.Create("main_menu");
}

// Destructor
MainMenu::~MainMenu()
{}

// Called before render is available
bool MainMenu::Awake(pugi::xml_node& node)
{
	LOG("Loading MainMenu");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool MainMenu::Start()
{
	app->guiManager->Enable();
	app->pauseMenu->Disable();
	playBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "PLAY", { 108, 300, 125, 20 }, this, {255, 255, 255});
	optionsBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "OPTIONS", { 108, 360, 125, 20 }, this, {255, 255, 255});
	creditsBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "CREDITS", { 108, 420, 125, 20 }, this, {255, 255, 255});
	exitBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "EXIT GAME", { 108, 480, 125, 20 }, this, {255, 255, 255});

	menuBtns.Add(playBtn);
	menuBtns.Add(optionsBtn);
	menuBtns.Add(creditsBtn);
	menuBtns.Add(exitBtn);


	newGameBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "NEW GAME", { 325, 300, 125, 20 }, this, { 255, 255, 255 });
	continueBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "CONTINUE", { 325, 380, 125, 20 }, this, { 255, 255, 255 });
	returnPlBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "RETURN", { 325, 460, 125, 20 }, this, { 255, 255, 255 });

	playBtns.Add(newGameBtn);
	playBtns.Add(continueBtn);
	playBtns.Add(returnPlBtn);

	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "CREDITS", { 550, 225, 70, 20 }, this, { 255,255,255, 1 }));
	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "Iván Jose Caballero - Team leader, art & music", { 415, 260, 70, 20 }, this, { 255,255,255, 1 }));
	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "Víctor Falcón - Managment, game design, coding", { 415, 285, 70, 20 }, this, { 255,255,255, 1 }));
	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "Pol Farreras - Game design, coding", { 415, 310, 70, 20 }, this, { 255,255,255, 1 }));
	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "Laura Isidro - Coding, design", { 415, 335, 70, 20 }, this, { 255,255,255, 1 }));
	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "Sofia Liles - Game artist, Q&A", { 415, 360, 70, 20 }, this, { 255,255,255, 1 }));
	credits.Add((GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 40, "Marta Llurba - Game artist, Q&A, UI", { 415, 385, 70, 20 }, this, { 255,255,255, 1 }));


	for (int i = 0; i < credits.Count(); i++)
	{
		credits.At(i)->data->state = GuiControlState::DISABLED;
	}

	
	musicSldr = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 9, "MUSIC", { 370, 280, 220, 20 }, this);
	musicSldr->SetValues(100, 1, 50);
	soundSlrd = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 10, "SOUND FX", { 370, 320, 220, 20 }, this);
	soundSlrd->SetValues(100, 1, 50);
	fullscreenChkbx = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 11, "FULLSCREEN", { 370, 375, 25, 25 }, this);
	vsyncChkbx = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 12, "VSYNC            ", { 370, 420, 25, 25 }, this);
	returnOPBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "RETURN", { 370, 460, 125, 20 }, this, { 255, 255, 255 });

	optionsBtns.Add(musicSldr);
	optionsBtns.Add(soundSlrd);
	optionsBtns.Add(fullscreenChkbx);
	optionsBtns.Add(vsyncChkbx);
	optionsBtns.Add(returnOPBtn);

	noBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "NO", { 500, 350, 25, 20 }, this, {255, 255, 255, 1});
	yesBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "YES", { 675, 350, 30, 20 }, this, {255, 255, 255, 1});
	exitText = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 200, "ARE YOU SURE YOU WANT TO EXIT?", { 475, 325, 420, 15 }, this, {255, 255, 255, 1});

	exitBtns.Add(noBtn);
	exitBtns.Add(yesBtn);

	newGameBtn->state = GuiControlState::DISABLED;
	continueBtn->state = GuiControlState::DISABLED;
	returnPlBtn->state = GuiControlState::DISABLED;


	musicSldr->state = GuiControlState::DISABLED;
	soundSlrd->state = GuiControlState::DISABLED;
	fullscreenChkbx->state = GuiControlState::DISABLED;
	vsyncChkbx->state = GuiControlState::DISABLED;
	returnOPBtn->state = GuiControlState::DISABLED;
	
	yesBtn->state = GuiControlState::DISABLED;
	noBtn->state = GuiControlState::DISABLED;
	exitText->state = GuiControlState::DISABLED;

	titleSFX = app->audio->LoadFx("Assets/Audio/Fx/title.wav");
	background = app->tex->Load("Assets/Menus/portada.png");
	title = app->tex->Load("Assets/Menus/title.png");
	menus = app->tex->Load("Assets/Menus/menus.png");
	app->audio->ChangeMusic(1);

	time.Start();
	return true;
}

// Called each loop iteration
bool MainMenu::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool MainMenu::Update(float dt)
{
	app->render->DrawTexture(background, 0, 0, NULL, true);

	if (currentPositionY < finalPositionY)
	{
		currentPositionY = EaseBounceInOut(currentTime, startPositionY, finalPositionY - startPositionY, duration);
		currentTime++;
	}
	app->render->DrawTexture(title, 0, currentPositionY, NULL, true);
	
	vsyncChkbx->checked = app->render->vsync;
	fullscreenChkbx->checked = app->win->fullscreen;

	app->audio->volFX = soundSlrd->value;
	app->audio->volMusic = musicSldr->value;

	UpdateInput();
	DrawMenu();
	return true;
}

void MainMenu::DrawMenu()
{
	SDL_Rect recttt{ 0, 0, 188, 230 };
	app->render->DrawTexture(menus, 75, 285, &recttt, true);
	if (optionsB)
	{
		SDL_Rect rect{ 270, 257, 411, 152 };
		app->render->DrawTexture(menus, 325, 250, &rect, true);
		returnPlBtn->state = GuiControlState::DISABLED;
	}
	else
	{
		returnOPBtn->state = GuiControlState::DISABLED;
	}
	if (play)
	{
		SDL_Rect rect{ 0, 0, 188, 230 };
		app->render->DrawTexture(menus, 290, 285, &rect, true);
		returnOPBtn->state = GuiControlState::DISABLED;
	}
	else
	{
		returnPlBtn->state = GuiControlState::DISABLED;
	}
	if (creditsB)
	{
		SDL_Rect rect{ 643, 0, 413, 257 };
		app->render->DrawTexture(menus, 400, 200, &rect, true);
	}
	if (exit)
	{
		SDL_Rect rect{ 1056, 0, 328, 87 };
		app->render->DrawTexture(menus, 450, 300, &rect, true);
	}
	else
	{
		noBtn->state = GuiControlState::DISABLED;
	}
}

void MainMenu::UpdateInput()
{
	/*GamePad& pad = app->input->pads[0];
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
	currentControl->data->state = GuiControlState::FOCUSED;*/
}

// Called each loop iteration
bool MainMenu::PostUpdate()
{
	bool ret = true;

	return ret;
}


// Called before quitting
bool MainMenu::CleanUp()
{
	LOG("Freeing scene");
	app->guiManager->Disable();
	
	app->tex->UnLoad(arrow);
	app->tex->UnLoad(background);
	app->tex->UnLoad(title);
	app->tex->UnLoad(menus);
	playBtns.Clear();
	menuBtns.Clear();
	optionsBtns.Clear();
	exitBtns.Clear();
	

	return true;
}

bool MainMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	bool ret = true;
	if (control->id == 1)
	{
		play = true;
		//PLAY
		for (int i = 0; i < playBtns.Count(); i++)
		{
			playBtns.At(i)->data->state = GuiControlState::NORMAL;
		}
	}
	if (control->id == 2)
	{
		optionsB = true;
		//OPTIONS
		for (int i = 0; i < optionsBtns.Count(); i++)
		{
			optionsBtns.At(i)->data->state = GuiControlState::NORMAL;
		}
	}
	if (control->id == 3)
	{
		creditsB = !creditsB;
		//CREDITS
		if (credits.At(1)->data->state == GuiControlState::DISABLED)
		{
			for (int i = 0; i < credits.Count(); i++)
			{
				credits.At(i)->data->state = GuiControlState::NORMAL;
			}
		}
		else
		{
			for (int i = 0; i < credits.Count(); i++)
			{
				credits.At(i)->data->state = GuiControlState::DISABLED;
			}
		}
	}
	if (control->id == 4)
	{
		exit = true;
		//EXIT
		for (int i = 0; i < exitBtns.Count(); i++)
		{
			exitBtns.At(i)->data->state = GuiControlState::NORMAL;
		}
		exitText->state = GuiControlState::NORMAL;
	}
	if (control->id == 5)
	{
		//NEW GAME
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->scene);
	}
	if (control->id == 6)
	{
		//CONTINUE
		app->fadeToBlack->MFadeToBlack(this, (Module*)app->scene);
		app->scene->load = true;
	}
	if (control->id == 7)
	{
		play = false;
		//RETURN
		for (int i = 0; i < playBtns.Count(); i++)
		{
			playBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		returnPlBtn->state = GuiControlState::DISABLED;
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
		optionsB = false;
		//RETURN
		for (int i = 0; i < optionsBtns.Count(); i++)
		{
			optionsBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		returnOPBtn->state = GuiControlState::DISABLED;
	}
	if (control->id == 14)
	{
		exit = false;
		//NO
		for (int i = 0; i < exitBtns.Count(); i++)
		{
			exitBtns.At(i)->data->state = GuiControlState::DISABLED;
		}
		exitText->state = GuiControlState::DISABLED;
	}
	if (control->id == 15)
	{
		//YES
		ret = false;
	}
	return ret;
}
