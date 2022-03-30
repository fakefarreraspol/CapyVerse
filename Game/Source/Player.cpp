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

void Player::AddCapybaraToBatle(Capybara* capybara)
{
	battleTeam.Add(capybara);
}
//TODO: Update the player input and move the player
void Player::UpdateInput()
{
}

List<Capybara*>& Player::GetBattleTeam()
{
	return battleTeam;
}

List<Capybara*>& Player::GetTeam()
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

void Player::SetCombat(bool value)
{
	for (ListItem<Capybara*>* member = battleTeam.start; member != nullptr; member = member->next)
	{
		member->data->SetCombat(value);
	}
}

