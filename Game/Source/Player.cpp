#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Log.h"
#include "Player.h"
#include "Physics.h"
#include "Timer.h"
#include "Window.h"
#include "Textures.h"
#include "Map.h"
#include "FadeToBlack.h"
#include "Inventory.h"
#include "StatsMenu.h"
 


Player::Player(iPoint position, uint32 id, const char* name) : Entity(EntityType::PLAYER, id, name, position)
{
	idle.PushBack({ 0,0,66,66 });
	
	walkRight.PushBack( { 66, 0, 66 , 66 });
	walkRight.PushBack( { 66 * 2, 0, 66 , 66 });
	walkRight.PushBack( { 66 * 3, 0, 66 , 66 });
	walkRight.PushBack( { 66 * 4, 0, 66 , 66 });

	walkRight.loop = true;
	walkRight.speed = 0.1f;
	
	walkLeft.PushBack({ 66, 0, 66 , 66 });
	walkLeft.PushBack({ 66 * 2, 0, 66 , 66 });
	walkLeft.PushBack({ 66 * 3, 0, 66 , 66 });
	walkLeft.PushBack({ 66 * 4, 0, 66, 66 });
	walkLeft.loop = true;
	walkLeft.speed = 0.1f;

	walkUp.PushBack({ 0, 66, 66 , 66 });
	walkUp.PushBack({ 66, 66, 66 , 66 });
	walkUp.PushBack({ 66*2, 66, 66 , 66 });
	walkUp.PushBack({ 66*3, 66, 66 , 66 });
	walkUp.PushBack({ 66*4, 66, 66 , 66 });
	walkUp.PushBack({ 66*5, 66, 66 , 66 });
	walkUp.PushBack({ 66*6, 66, 66 , 66 });
	
	walkUp.loop = true;
	walkUp.speed = 0.1f;
	
	walkDown.PushBack({ 66*8, 66, 66 , 66  });
	walkDown.PushBack({ 66*9, 66, 66 , 66 });
	walkDown.PushBack({ 66 * 10, 66, 66 , 66  });
	walkDown.PushBack({ 66 * 11, 66, 66 , 66});
	walkDown.PushBack({ 66 * 12, 66, 66 , 66 });
	walkDown.PushBack({ 66 * 13, 66, 66 , 66 });
	walkDown.PushBack({ 66 * 14, 66, 66 , 66});
	
	walkDown.speed = 0.1f;
	walkDown.loop = true;
	currentAnim->SetAnim(idle);

	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::DYNAMIC);
	collider->listener = (Module*)app->entMan;
	collider->eListener = this;
	collider->body->SetFixedRotation(true);

	w = 66;
	h = 66;
}

Player::~Player()
{
}
bool Player::Start()
{
	if (!collider)
	{
		collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::DYNAMIC);
		collider->listener = (Module*)app->entMan;
		collider->eListener = this;
		collider->body->SetFixedRotation(true);
	}
	return true;
}

bool Player::Update(float dt)
{
	bool ret = true;
	if(app->GetDebug())
		printf("x:%i y:%i\n", position.x, position.y);


	UpdateCamera();

	if (canMove)
		UpdateInput(dt);
	else
		collider->body->SetLinearVelocity({ 0.0f, 0.0f });

	if (initDebug)
	{
		Debug();
		initDebug = false;
	}
	currentAnim->Update();
	return ret;
}

void Player::Debug()
{
	if (!app->GetDebug())
	{
		velocity = 10.0f;
		app->colManager->world->DestroyBody(collider->body);
		collider = app->colManager->CreateRectangleSensor(position.x, position.y, 32, 32, bodyType::DYNAMIC);
	}
	else
	{
		app->colManager->world->DestroyBody(collider->body);
		collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::DYNAMIC);
		collider->listener = (Module*)app->entMan;
		collider->eListener = this;
		collider->body->SetFixedRotation(true);
		velocity = 2.0f;
	}
}

void Player::UpdateCamera()
{
		uint w, h;
		app->win->GetWindowSize(w, h);
		app->render->camera.x = w / 2 - position.x;
		app->render->camera.y = h / 2 - position.y;
	if (!app->GetDebug())
	{
		//Setting the camera borders	
		uint32_t maxX = app->mapManager->maxX;
		uint32_t minX = app->mapManager->minX;
		uint32_t maxY = app->mapManager->maxY;
		uint32_t minY = app->mapManager->minY;

		if (position.x <= minX)
			app->render->camera.x = w / 2 - minX;

		if (position.y >= maxY)
			app->render->camera.y = h / 2 - maxY;

		if (position.x >= maxX)
			app->render->camera.x = w / 2 - maxX;

		if (position.y <= minY)
			app->render->camera.y = h / 2 - minY;
	}
}

void Player::AddCapybara(Capybara* capybara)
{
	team.Add(capybara);
}

void Player::AddCapybaraToBatle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}
//TODO: Update the player input and move the player
void Player::UpdateInput(float dt)
{

	

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		initDebug = true;


	position.x = METERS_TO_PIXELS(collider->body->GetPosition().x);
	position.y = METERS_TO_PIXELS(collider->body->GetPosition().y);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		faceLeft = true;
		collider->body->SetLinearVelocity({ velocity, 0.0f });
		if (currentAnim->ref != &walkLeft)
		{
			walkLeft.Reset();
			currentAnim->SetAnim(walkLeft);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		faceLeft = false;
		collider->body->SetLinearVelocity({ -velocity, 0.0f });
		if (currentAnim->ref != &walkRight)
		{
			walkRight.Reset();
			currentAnim->SetAnim(walkRight);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		collider->body->SetLinearVelocity({ 0.0f, -velocity });
		if (currentAnim->ref != &walkUp)
		{
			walkUp.Reset();
			currentAnim->SetAnim(walkUp);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		collider->body->SetLinearVelocity({ 0.0f, velocity });
		if (currentAnim->ref != &walkDown)
		{
			walkDown.Reset();
			currentAnim->SetAnim(walkDown);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE)
	{
		collider->body->SetLinearVelocity({ 0.0f,0.0f });
		if (currentAnim->ref != &idle) 
		{
			idle.Reset();
			currentAnim->SetAnim(idle);
		}
	}

	if (app->GetDebug())
	{
		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		{
			app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene1, 2);
		}
		if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene2, 2);
		}
		if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			app->fadeToBlack->MFadeToBlack((Module*)app->scene, (Module*)app->battleScene3, 2);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		if (!app->statsMenu->IsEnabled())
			app->statsMenu->Enable();
		else
			app->statsMenu->ActivateMenu();
		
	}
}

List<Capybara*>& Player::GetBattleTeam()
{
	return battleTeam;
}

List<Capybara*>& Player::GetTeam()
{
	return team;
}

bool Player::LoadState(pugi::xml_node& node)
{
	position.x = node.child("position").attribute("x").as_float();
	position.y = node.child("position").attribute("y").as_float();

	collider->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0.0f);
	isBattle = node.attribute("isBattle").as_bool();
	money = node.attribute("money").as_int();

	active = node.attribute("active").as_bool();
	renderable = node.attribute("renderable").as_bool();

	return false;
}

bool Player::SaveState(pugi::xml_node& node)
{
	pugi::xml_node position = node.append_child("position");
	position.append_attribute("x").set_value(this->position.x);
	position.append_attribute("y").set_value(this->position.y);
	node.append_attribute("id").set_value(id);
	node.append_attribute("isBattle").set_value(isBattle);
	node.append_attribute("money").set_value(money);

	node.append_attribute("active").set_value(active);
	node.append_attribute("renderable").set_value(renderable);

	return true;
}

void Player::SetCombat(bool value)
{
	for (int i = 0; i < battleTeam.Count(); i++)
	{
		battleTeam.At(i)->data->SetCombat(value);
	}
	this->isBattle = value;
}

void Player::OnCollision(PhysBody* c1, PhysBody* c2)
{
	printf("Collision with player\n");
}

bool Player::CleanUp()
{
	return true;
}
