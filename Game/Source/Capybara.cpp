#include <stdlib.h>

#include "Log.h"

#include "Capybara.h"
#include "Input.h"
#include "App.h"



Capybara::Capybara(CapybaraType capyType, uint32 id, iPoint position, const char* name) : Entity(EntityType::CAPYBARA, id, name, position), capybaraType(capyType)
{
	lvl = 1;

	//Change this values in order to balance the game progression
	xpNext = 50;
	healthXLvl = 10;
	manaXLvl = 7;
	damageXLvl = 4;
	armorXLvl = 3;

	
}

Capybara::~Capybara()
{
}

bool Capybara::Update(float dt)
{
	bool ret = true;
		
	if (xp >= xpNext)
		LevelUp();

	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		LevelUp();

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		AddXp(10);

	if (this->health <= 0)
	{
		isCombat = false;
	}

	return ret;
}

bool Capybara::Draw(Render* render)
{
	bool ret = true;
	if (isCombat)
	{
		render->DrawRectangle({position.x, position.y, 64, 64}, 255, 0, 0);
	}

	return ret;
}

int& Capybara::GetHealth()
{
	return health;
}

int& Capybara::GetMaxHealth()
{
	return maxHealth;
}

int& Capybara::GetMana()
{
	return mana;
}

int& Capybara::GetMaxMana()
{
	return maxMana;
}

int& Capybara::GetDamage()
{
	return damage;
}

int& Capybara::GetArmor()
{
	return armor;
}

int& Capybara::GetXP()
{
	return xp;
}

int& Capybara::GetNextXP()
{
	return xpNext;
}

CapybaraType& Capybara::GetType()
{
	return capybaraType;
}

CapybaraStats& Capybara::GetStats()
{
	return capybaraStats;
}

CapybaraStatus& Capybara::GetStatus()
{
	return capybaraStatus;
}

void Capybara::Damage(int value)
{ 	
	if (health - value > 0)
	{
		health -= value;
		return;
	}
	
	health = 0;

	return;
}

void Capybara::Heal(int value)
{
	if (value + health < maxHealth)
	{
		health += value;
		return;
	}

	health = maxHealth;

	return;
}
//TODO: Think about all the abilities
void Capybara::UseAbility(Capybara* target)
{
	return;
}

void Capybara::Attack(Capybara* target)
{
	//Formula DMG = D * (D + 100) * 0.08 / (A + 8)
	//D -- Attack value
	//A -- Character armor
	if (target == nullptr)
		return;
	int finalDamage = this->damage* (this->damage + 100) * 0.08 / (target->armor + 8);
	target->Damage(finalDamage);

	canAttack = false;
	printf("%s id: %i DMG: %i to %s id: %i", this->name.GetString(), this->id, finalDamage, target->name.GetString(), target->id);
}

void Capybara::SetStatus(CapybaraStatus status)
{
	this->capybaraStatus = status;
}

void Capybara::SetAttack()
{
	canAttack = true;
}

bool Capybara::CanAttack()
{
	return canAttack;
}

void Capybara::LevelUp()
{
	lvl++;
	xpNext = xpNext + xpNext * 0.1f;
	switch (capybaraType)
	{
	//Each capybara levels up 1 point per level or 2 depending on their type
	case CapybaraType::NONE:
	{
		capybaraStats.hp++;
		capybaraStats.mp++;
		capybaraStats.strenght++;
		capybaraStats.speed++;
		capybaraStats.armor++;
		capybaraStats.intelligence++;
	}break;
	//Tank levels up 2 points on hp and armor
	case CapybaraType::TANK:
	{
		capybaraStats.hp += 2;
		capybaraStats.mp++;
		capybaraStats.strenght++;
		capybaraStats.speed++;
		capybaraStats.armor += 2;
		capybaraStats.intelligence++;
	}break;
	//DPS levels up 2 points on speed and strength
	case CapybaraType::DPS:
	{
		capybaraStats.hp++;
		capybaraStats.mp++;
		capybaraStats.strenght += 2;
		capybaraStats.speed += 2;
		capybaraStats.armor++;
		capybaraStats.intelligence++;
	}break;
	//Supp levels up 2 points on mp and intelligence
	case CapybaraType::SUPP:
	{
		capybaraStats.hp++;
		capybaraStats.mp += 2;
		capybaraStats.strenght++;
		capybaraStats.speed++;
		capybaraStats.armor++;
		capybaraStats.intelligence += 2;
	}break;
	default: 
		break;
	}
	
	//Healing a proporitonal amount after lvlup
	Heal(0.5 * maxHealth);
	
	//Updating all the stats 
	UpdateStats();

	//Debug log
	LOG("");
	LOG("%s stats LVL: %i", name.GetString(), lvl);
	LOG("HP: %i MXHP: %i HPLVL: %i", health, maxHealth, capybaraStats.hp);
	LOG("MP: %i MXMP: %i MPLVL: %i", mana, maxMana, capybaraStats.mp);
	LOG("DMG: %i STRLVL: %i", damage, capybaraStats.strenght);
	LOG("ARLVL: %i", capybaraStats.armor);
	LOG("INTLVL: %i", capybaraStats.intelligence);
	LOG("SPDLVL: %i", capybaraStats.speed);
	LOG("XP: %i XPNLVL: %i", xp, xpNext);

	return;
}

void Capybara::AddXp(int value)
{
	xp += value;
	return;
}

bool Capybara::LoadState(pugi::xml_node&)
{
	return false;
}

bool Capybara::SaveState(pugi::xml_node&)
{
	return false;
}

void Capybara::SetCombat(bool value)
{
	isCombat = value;
}

void Capybara::UpdateStats()
{
	maxHealth = capybaraStats.hp * healthXLvl;
	maxMana = capybaraStats.mp * manaXLvl;
	damage = capybaraStats.strenght * damageXLvl;
	armor = capybaraStats.armor * armorXLvl;
}

void Capybara::InitStats()
{
	UpdateStats();
	health = maxHealth;
	mana = maxMana;
}
