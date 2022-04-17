#include "MainMenu.h"

#include "App.h"
#include "FadeToBlack.h"
#include "GuiManager.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"

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

	playBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "PLAY", { 108, 300, 125, 20 }, this, {255, 255, 255});
	optionsBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "OPTIONS", { 108, 360, 125, 20 }, this, {255, 255, 255});
	creditsBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "CREDITS", { 108, 420, 125, 20 }, this, {255, 255, 255});
	exitBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "EXIT GAME", { 108, 480, 125, 20 }, this, {255, 255, 255});

	newGameBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "NEW GAME", { 325, 300, 125, 20 }, this, { 255, 255, 255 });
	continueBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "CONTINUE", { 325, 380, 125, 20 }, this, { 255, 255, 255 });
	returnPlBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "RETURN", { 325, 460, 125, 20 }, this, { 255, 255, 255 });

	volumeBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "VOLUME", { 325, 285, 125, 20 }, this, { 255, 255, 255 });
	musicSldr = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 9, "MUSIC", { 500, 280, 220, 20 }, this);
	soundSlrd = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 10, "SOUND FX", { 500, 320, 220, 20 }, this);
	fullscreenChkbx = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 11, "FULLSCREEN", { 505, 375, 25, 25 }, this);
	vsyncChkbx = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 12, "VSYNC", { 505, 420, 25, 25 }, this);
	returnOPBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "RETURN", { 325, 485, 125, 20 }, this, { 255, 255, 255 });

	noBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "NO", { 565, 380, 25, 20 }, this, {255, 255, 255, 1});
	yesBtn = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "YES", { 750, 380, 25, 20 }, this, {255, 255, 255, 1});
	exitText = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 200, "ARE YOU SURE YOU WANT TO EXIT THE GAME?", { 475, 325, 420, 15 }, this, {255, 255, 255, 1});

	newGameBtn->state = GuiControlState::DISABLED;
	continueBtn->state = GuiControlState::DISABLED;
	returnPlBtn->state = GuiControlState::DISABLED;

	volumeBtn->state = GuiControlState::DISABLED;
	musicSldr->state = GuiControlState::DISABLED;
	soundSlrd->state = GuiControlState::DISABLED;
	fullscreenChkbx->state = GuiControlState::DISABLED;
	vsyncChkbx->state = GuiControlState::DISABLED;
	returnOPBtn->state = GuiControlState::DISABLED;
	
	yesBtn->state = GuiControlState::DISABLED;
	noBtn->state = GuiControlState::DISABLED;
	exitText->state = GuiControlState::DISABLED;


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
	GamePad& pad = app->input->pads[0];
	return true;
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
	return true;
}

bool MainMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}
