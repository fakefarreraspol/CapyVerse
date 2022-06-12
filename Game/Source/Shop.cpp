#include "Shop.h"

Shop::Shop(bool startEnabled) : Module(startEnabled)
{
}

Shop::~Shop()
{
}

bool Shop::Awake(pugi::xml_node&)
{
	return false;
}

bool Shop::Start()
{
	return false;
}

bool Shop::PreUpdate()
{
	return false;
}

bool Shop::Update(float dt)
{
	return false;
}

bool Shop::PostUpdate()
{
	return false;
}

bool Shop::CleanUp()
{
	return false;
}

bool Shop::OnGuiMouseClickEvent(GuiControl* control)
{
	return false;
}
