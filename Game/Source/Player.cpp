#include "App.h"
#include "EntityManager.h"
#include "Input.h"

#include "Player.h"


Player::Player(iPoint position, uint32 id, const char* name) : Entity(EntityType::PLAYER, id, name, position)
{
}

Player::~Player()
{
}

bool Player::Update(float dt)
{
	bool ret = true;
	
	UpdateInput();

	return ret;
}

bool Player::Draw(Render* render)
{
	bool ret = true;
	return ret;
}

void Player::AddCapybara(Capybara* capybara)
{
	team.Add(capybara);
}

void Player::AddCapybaraToBatlle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}
//TODO: Update the player input and move the player
void Player::UpdateInput()
{
	GamePad& pad = app->input->pads[0];

	lastPos = position;

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		position.x -= speed;
		/*if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
			currentIdleAnim = leftIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_A;

		if (app->input->GetKey(SDL_SCANCODE_W)== KEY_REPEAT && isStuck)
		{
			position.y -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && isStuck)
		{
			position.y += speed;
			isStuck = false;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
	{
		position.x += speed;
		/*if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
			currentIdleAnim = rightIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_D;

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && isStuck)
		{
			position.y -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && isStuck)
		{
			position.y += speed;
			isStuck = false;
		}

	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) 
	{
		position.y += speed;
		/*if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
			currentIdleAnim = downIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_S;

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && isStuck)
		{
			position.x -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && isStuck)
		{
			position.x += speed;
			isStuck = false;
		}

	}
	else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		/*if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
			currentIdleAnim = upIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_W;

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && isStuck)
		{
			position.x -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && isStuck)
		{
			position.x += speed;
			isStuck = false;
		}
	}


	// GAMEPAD SUPPORT

	// Debug key for gamepad rumble testing purposes
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		app->input->ShakeController(0, 12, 0.33f);
	}

	// Debug key for gamepad rumble testing purposes
	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		app->input->ShakeController(0, 36, 0.66f);
	}

	// Debug key for gamepad rumble testing purposes
	if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		app->input->ShakeController(0, 60, 1.0f);
	}


	// Implement gamepad support

	if (pad.left_x < 0.0f || pad.left == true)
	{
		position.x -= speed;
		/*if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
			currentIdleAnim = leftIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_A;

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && isStuck)
		{
			position.y -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && isStuck)
		{
			position.y += speed;
			isStuck = false;
		}
	}

	if (pad.left_x > 0.0f || pad.right == true)
	{
		position.x += speed;
		/*if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
			currentIdleAnim = rightIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_D;

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && isStuck)
		{
			position.y -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && isStuck)
		{
			position.y += speed;
			isStuck = false;
		}
	}

	if (pad.left_y > 0.0f || pad.down == true)
	{
		position.y += speed;
		/*if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
			currentIdleAnim = downIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_S;

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && isStuck)
		{
			position.x -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && isStuck)
		{
			position.x += speed;
			isStuck = false;
		}
	}

	if (pad.left_y < 0.0f || pad.up == true)
	{
		position.y -= speed;
		/*if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
			currentIdleAnim = upIdleAnim;
		}*/
		lastKeyPressed = SDL_SCANCODE_W;

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && isStuck)
		{
			position.x -= speed;
			isStuck = false;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && isStuck)
		{
			position.x += speed;
			isStuck = false;
		}
	}
}

List<Capybara*> Player::GetBattleTeam()
{
	return battleTeam;
}

List<Capybara*> Player::GetTeam()
{
	return team;
}

bool Player::LoadState(pugi::xml_node&)
{
	return false;
}

bool Player::SaveState(pugi::xml_node&)
{
	return false;
}

