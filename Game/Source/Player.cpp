#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Log.h"
#include "Player.h"
#include "Physics.h"
#include "Timer.h"
#include "Window.h"
#include "Textures.h"

Player::Player(iPoint position, uint32 id, const char* name) : Entity(EntityType::PLAYER, id, name, position)
{
	idle.PushBack({ 0,0,66,66 });
	walkRight.PushBack( { 66, 0, 66 * 2, 66 });
	walkRight.PushBack( { 66 * 2, 0, 66 * 3, 66 });
	walkRight.PushBack( { 66 * 3, 0, 66 * 4, 66 });
	walkRight.PushBack( { 66 * 4, 0, 66 * 5, 66 });

	walkRight.loop = true;
	walkRight.speed = 0.1f;
	
	walkLeft.PushBack({ 66, 0, 66 * 2, 66 });
	walkLeft.PushBack({ 66 * 2, 0, 66 * 3, 66 });
	walkLeft.PushBack({ 66 * 3, 0, 66 * 4, 66 });
	walkLeft.PushBack({ 66 * 4, 0, 66 * 5, 66 });
	walkLeft.loop = true;
	walkLeft.speed = 0.1f;

	walkUp.PushBack({ 0, 66, 66 , 66*2 });
	walkUp.PushBack({ 66, 66, 66 * 2, 66*2 });
	walkUp.PushBack({ 66*2, 66, 66 * 3, 66*2 });
	walkUp.PushBack({ 66*3, 66, 66 * 4, 66 * 2 });
	walkUp.PushBack({ 66*4, 66, 66 * 5, 66 * 2 });
	walkUp.PushBack({ 66*5, 66, 66 * 6, 66 * 2 });
	walkUp.PushBack({ 66*6, 66, 66 * 7, 66 * 2 });
	walkUp.PushBack({ 66*7, 66, 66 * 8, 66 * 2 });
	walkLeft.loop = true;
	walkLeft.speed = 0.1f;
	
	walkDown.PushBack({ 0, 66, 66 , 66 * 2 });
	walkDown.PushBack({ 66, 66, 66 * 2, 66 * 2 });
	walkDown.PushBack({ 66 * 2, 66, 66 * 3, 66 * 2 });
	walkDown.PushBack({ 66 * 3, 66, 66 * 4, 66 * 2 });
	walkDown.PushBack({ 66 * 4, 66, 66 * 5, 66 * 2 });
	walkDown.PushBack({ 66 * 5, 66, 66 * 6, 66 * 2 });
	walkDown.PushBack({ 66 * 6, 66, 66 * 7, 66 * 2 });
	walkDown.PushBack({ 66 * 7, 66, 66 * 8, 66 * 2 });
	walkDown.speed = 0.1f;
	currentAnim = &idle;
}

Player::~Player()
{
}

bool Player::Update(float dt)
{
	bool ret = true;
	
	UpdateCamera();
	if (load)
	{
		texture  = app->tex->Load("Assets/Textures/Sprites/characters.png");
		load = false;
	}

	if (canMove == true)
		UpdateInput(dt);

	if (app->GetDebug())
		speed = 0.2f;
	else
		speed = 0.1f;

	return ret;
}

void Player::UpdateCamera()
{

	uint w, h;
	app->win->GetWindowSize(w, h);
	app->render->camera.x = w / 2 - position.x;
	app->render->camera.y = h / 2 - position.y;
	if (w / 2 - position.x < 0)
	{
		app->render->camera.y = 0;
	}
	if (h / 2 - position.y < 0)
	{
		app->render->camera.x = 0;
	}

}

bool Player::Draw(Render* render)
{
	bool ret = true;
	if (!isBattle)
	{
		//render->DrawTexture(texture, position.x, position.y, &currentAnim->GetCurrentFrame());
		app->render->DrawTexture(texture, position.x - 32, position.y - 48, &currentAnim->GetCurrentFrame());
	}
	currentAnim->Update();
	return ret;
}

bool Player::Start()
{
	collider = app->colManager->CreateRectangle(position.x, position.y, 32, 32, bodyType::DYNAMIC);
	collider->listener = (Module*)app->entMan;
	collider->eListener = this;
	collider->body->SetFixedRotation(true);
	return true;
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
	GamePad& pad = app->input->pads[0];
	lastPos = position;

	position.x = METERS_TO_PIXELS(collider->body->GetPosition().x);
	position.y = METERS_TO_PIXELS(collider->body->GetPosition().y);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		collider->body->SetLinearVelocity({ velocity, 0.0f });
		if (currentAnim != &walkLeft)
		{
			walkLeft.Reset();
			currentAnim = &walkLeft;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		collider->body->SetLinearVelocity({ -velocity, 0.0f });
		if (currentAnim != &walkRight)
		{
			walkRight.Reset();
			currentAnim = &walkRight;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		collider->body->SetLinearVelocity({ 0.0f, -velocity });
		if (currentAnim != &walkUp)
		{
			walkUp.Reset();
			currentAnim = &walkUp;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		collider->body->SetLinearVelocity({ 0.0f, velocity });
		if (currentAnim != &walkDown)
		{
			walkDown.Reset();
			currentAnim = &walkDown;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE)
	{
		collider->body->SetLinearVelocity({ 0.0f,0.0f });
		if (currentAnim != &idle) 
		{
			idle.Reset();
			currentAnim = &idle;
		}
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

}

bool Player::CleanUp()
{
	return true;
}
