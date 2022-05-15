#include "End.h"
#include "Input.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"


End::End(bool startEnabled) : Module(startEnabled)
{
}

End::~End()
{
}

bool End::Awake(pugi::xml_node&)
{
	return true;
}

bool End::Start()
{
	background = app->tex->Load("Assets/");
	return true;
}

bool End::PreUpdate()
{
	return true;
}

bool End::Update(float dt)
{
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		ret = false;
	}

	app->render->DrawTexture(background, 0, 0);
	return ret;
}

bool End::PostUpdate()
{
	return true;
}

bool End::CleanUp()
{
	return true;
}
