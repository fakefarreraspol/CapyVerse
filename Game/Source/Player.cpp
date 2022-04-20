#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Log.h"
#include "Player.h"
#include "Collisions.h"
#include "Timer.h"

Player::Player(iPoint position, uint32 id, const char* name) : Entity(EntityType::PLAYER, id, name, position)
{
	collider = app->colManager->AddCollider({ position.x, position.y, 64, 64 }, Collider::Type::PLAYER, (Module*)app->entMan, this);
}

Player::~Player()
{
}

bool Player::Update(float dt)
{
	bool ret = true;
	

	collider->SetPos(position.x, position.y);
	UpdateInput(dt);

	if (app->GetDebug())
		speed = 0.2f;
	else
		speed = 0.1f;

	return ret;
}

bool Player::Draw(Render* render)
{
	bool ret = true;
	if (!isBattle)
	{
		//if(app->GetDebug())
			render->DrawRectangle({ position.x, position.y,  64 , 64 }, 255, 255, 0);

		//render->DrawTexture(texture, position.x, position.y, &currentAnim->GetCurrentFrame());
	}
	return ret;
}

bool Player::Start()
{
	collider = app->colManager->AddCollider({ position.x, position.y, 64, 64 }, Collider::Type::PLAYER, (Module*)app->entMan, this);
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

	

	int inputs = 0;
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		inputs++;
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		inputs++;
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		inputs++;
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		inputs++;


	float mov = speed * dt;
	if (inputs > 1)
		mov *= sqrt(2) / 2;		// sine of 45


	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= mov;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += mov;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= mov;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += mov;
	}



	//// GAMEPAD SUPPORT


	//	// GAMEPAD SUPPORT

	//	// Debug key for gamepad rumble testing purposes
	//	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	//	{
	//		app->input->ShakeController(0, 12, 0.33f);
	//	}

		// Implement gamepad support
	
		
	LOG("%2.2f", pad.left_x);
	LOG("%2.2f", pad.left_y);
	if (pad.left_x < 0.0f || pad.left == true)
	{
		position.x -= speed * dt * -pad.left_x;
	}
	if (pad.left_x > 0.0f || pad.right == true)
	{
		position.x += speed * dt * pad.left_x;
	}
	if (pad.left_y > 0.0f || pad.down == true)
	{
		position.y += speed * dt * pad.left_y;
	}

	if (pad.left_y < 0.0f || pad.up == true)
	{
		position.y -= speed * dt * -pad.left_y;
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


void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (!app->GetDebug())
	{
		if (c1->type == Collider::PLAYER)
		{
			if (c2->type == Collider::WALL)
			{
				wallsDetected++;

				int difference = c1->rect.w;

				if (c1->GetPos().x <= c2->GetPos().x)
				{
					if (difference > c1->rect.w - (c2->rect.x - c1->rect.x))
					{
						difference = c1->rect.w - (c2->rect.x - c1->rect.x);
						lastKeyPressed = SDL_SCANCODE_D;
					}
				}
				else
				{
					if (difference > c2->rect.w - (c1->rect.x - c2->rect.x))
					{
						difference = c2->rect.w - (c1->rect.x - c2->rect.x);
						lastKeyPressed = SDL_SCANCODE_A;
					}
				}
				if (c1->GetPos().y <= c2->GetPos().y)
				{
					if (difference > c1->rect.h - (c2->rect.y - c1->rect.y))
					{
						difference = c1->rect.h - (c2->rect.y - c1->rect.y);
						lastKeyPressed = SDL_SCANCODE_S;
					}
				}
				else
				{
					if (difference > c2->rect.h - (c1->rect.y - c2->rect.y))
					{
						difference = c2->rect.h - (c1->rect.y - c2->rect.y);
						lastKeyPressed = SDL_SCANCODE_W;
					}
				}

				switch (lastKeyPressed)
				{
				case SDL_SCANCODE_A:	position.x++;	break;
				case SDL_SCANCODE_D:	position.x--;	break;
				case SDL_SCANCODE_W:	position.y++;	break;
				case SDL_SCANCODE_S:	position.y--;	break;
				default:
					break;
				}
				
				

				/*if (c1->GetPos().x <= c2->GetPos().x)
					position.x--;
				if (c1->GetPos().x >= c2->GetPos().x)
					position.x++;
				if (c1->GetPos().y <= c2->GetPos().y)
					position.y--;
				if (c1->GetPos().y >= c2->GetPos().y)
					position.y++;*/



			}
			
		}
	}
}

bool Player::CleanUp()
{
	app->colManager->RemoveCollider(collider);
	return true;
}
