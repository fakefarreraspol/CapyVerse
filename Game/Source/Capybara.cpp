#include <stdlib.h>

#include "Log.h"

#include "Capybara.h"
#include "Input.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Inventory.h"
#include "EntityManager.h"

Capybara::Capybara(CapybaraType capyType, uint32 id, iPoint position, const char* name) : Entity(EntityType::CAPYBARA, id, name, position), capybaraType(capyType)
{
	level = 1;
	capyName.Create(name);


	//Change this values in order to balance the game progression
	xpNext = 50;
	healthXLvl = 10;
	manaXLvl = 7;
	damageXLvl = 4;
	armorXLvl = 3;

	this->Disable();
	
}

Capybara::~Capybara()
{
	
}

bool Capybara::Start()
{
	
	return true;
}

bool Capybara::Update(float dt)
{
	bool ret = true;
	if (load)
	{
		/*attackSFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-attack4.wav");
		abilitySFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-attack2.wav");
		healSFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-spell1.wav");
		hitSFX = app->audio->LoadFx("Assets/Audio/Fx/capybara-chirp.wav");*/
		load = false;
	}
	if (xp >= xpNext)
		LevelUp();

	

	if (this->health <= 0)
	{
		isCombat = false;
	}

	return ret;
}

void Capybara::SetLevel(int level)
{
	for (int i = 0; i < level - this->level; i++)
	{
		LevelUp();
	}
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

int& Capybara::GetLVL()
{
	return level;
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

CapybaraTarget& Capybara::GetTarget()
{
	return capybaraTarget;
}

void Capybara::Damage(int value)
{ 	
	if (value <= 0)
		return;
	if (health - value > 0)
	{
		health -= value;
		return;
	}
	app->audio->PlayFx(hitSFX);
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
	app->audio->PlayFx(healSFX);
	return;
}
void Capybara::RestoreMana(int value)
{
	if (value + mana < maxMana)
	{
		mana += value;
		return;
	}
	app->audio->PlayFx(healSFX);
	mana = maxMana;

	return;
}
//TODO: Think about all the abilities
bool Capybara::UseAbility(Capybara* target)
{
	return true;
}

void Capybara::Attack(Capybara* target)
{
	//Formula DMG = D * (D + 100) * 0.08 / (A + 8)
	//D -- Attack value
	//A -- Character armor
	if (target == nullptr)
		return;
	int finalDamage = this->damage * (int)((this->damage + 100) * 0.08f)/ (target->armor + 8);
	target->Damage(finalDamage);
	app->audio->PlayFx(attackSFX);
	canAttack = false;
	printf("%s id: %i DMG: %i to %s id: %i\n", this->capyName.GetString(), this->id, finalDamage, target->capyName.GetString(), target->id);
}

void Capybara::SetStatus(CapybaraStatus status)
{
	this->capybaraStatus = status;
	switch (status)
	{
	case CapybaraStatus::NONE:		statusCounter = 0;	break;
	case CapybaraStatus::POISONED:	statusCounter = 3;	break;
	case CapybaraStatus::SLEEP:		statusCounter = 3;  break;
	case CapybaraStatus::BLEED:		statusCounter = 2;	break;
	case CapybaraStatus::BLOATED:	statusCounter = 4;	break;
	case CapybaraStatus::STUNED:	statusCounter = 2;	break;
	case CapybaraStatus::TAUNTED:	statusCounter = 1;	break;
	case CapybaraStatus::DEFENSIVE: statusCounter = 1;	break;
	case CapybaraStatus::RAGE:		statusCounter = 2;	break;
	case CapybaraStatus::CLEVER:	statusCounter = 1;	break;
	}
}



void Capybara::SetAttack(bool isAbleToAttack)
{
	canAttack = isAbleToAttack;
}

bool Capybara::CanAttack()
{
	return canAttack;
}

void Capybara::UpdateStatus()
{
	if (statusCounter > 0)
	{
		switch (capybaraStatus)
		{
		case CapybaraStatus::POISONED:
		{
			Damage(rand() % capybaraStats.hp + 1);
		}break;
		case CapybaraStatus::SLEEP:
		{

		}break;
		case CapybaraStatus::BLEED:
		{
		}break;
		case CapybaraStatus::TAUNTED:
		{
		}break;
		}
		statusCounter--;
	}
	else
	{
		switch (capybaraStatus)
		{

		case CapybaraStatus::BLOATED:
		{
			capybaraStats.speed += (int)(capybaraStats.speed * 0.2f);
		}break;
		case CapybaraStatus::STUNED:
		{
			capybaraStats.intelligence += (int)(capybaraStats.intelligence * 0.5f);
		}break;
		case CapybaraStatus::DEFENSIVE:
		{
			capybaraStats.armor -= 5;
		}break;
		case CapybaraStatus::RAGE:
		{
			capybaraStats.strenght -= 5;
		}break;
		case CapybaraStatus::CLEVER:
		{
			capybaraStats.intelligence -= 5;
		}break;
		}
		this->SetStatus(CapybaraStatus::NONE);
		UpdateStats();
	}
}

void Capybara::LevelUp()
{
	level++;
	xpNext = xpNext + xpNext * 0.1f;
	xp = 0;
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
	Heal(0.5f * maxHealth);
	RestoreMana(0.5f * maxMana);
	//Updating all the stats 
	UpdateStats();

	//Debug log
	LOG("");
	LOG("%s stats LVL: %i", capyName.GetString(), level);
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

bool Capybara::LoadState(pugi::xml_node& node)
{
	position.x = node.child("position").attribute("x").as_int();
	position.y = node.child("position").attribute("y").as_int();

	level = node.attribute("level").as_int();
	health = node.attribute("health").as_int();
	xp = node.attribute("xp").as_int();
	mana = node.attribute("mana").as_int();
	capybaraType = (CapybaraType)node.attribute("type").as_int();
	capybaraTarget = (CapybaraTarget)node.attribute("target").as_int();
	active = node.attribute("active").as_bool();
	renderable = node.attribute("renderable").as_bool();

	// must update other stats depending on level

	return false;
}

bool Capybara::SaveState(pugi::xml_node& node)
{
	pugi::xml_node position = node.append_child("position");
	position.append_attribute("x").set_value(this->position.x);
	position.append_attribute("y").set_value(this->position.y);

	node.append_attribute("id").set_value(id);
	node.append_attribute("level").set_value(level);
	node.append_attribute("health").set_value(health);
	node.append_attribute("xp").set_value(xp);
	node.append_attribute("mana").set_value(mana);
	node.append_attribute("type").set_value((int)capybaraType);
	node.append_attribute("target").set_value((int)capybaraTarget);
	node.append_attribute("active").set_value(active);
	node.append_attribute("renderable").set_value(renderable);

	return false;
}

void Capybara::SetCombat(bool value)
{
	isCombat = value;
}

bool Capybara::GetCombat()
{
	return isCombat;
}

bool Capybara::CleanUp()
{
	return true;
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

void Capybara::SetStatsFromItem(ItemStats itemStats, bool sum)
{
	if (sum)
	{
		health += itemStats.hp;
		maxHealth += itemStats.hp;

		mana += itemStats.mp;
		maxMana += itemStats.mp;

		damage += itemStats.strenght;
		capybaraStats.speed += itemStats.speed;
		armor += itemStats.armor;
		
	}
	else
	{
		health -= itemStats.hp;
		maxHealth -= itemStats.hp;

		mana -= itemStats.mp;
		maxMana -= itemStats.mp;

		damage -= itemStats.strenght;
		capybaraStats.speed -= itemStats.speed;
		armor -= itemStats.armor;
	}
}

bool Capybara::UseItem(Item* item)
{
	bool ret = false;
	if (item->category == ItemCategory::CONSUMABLE)
	{
		Item* n = (Item*)app->entMan->CloneItem(item);
		
		consumables.Add(n);
		app->entMan->inventory->DelItem(item);
		ret = true;
	}
	return ret;
}
bool Capybara::EquipItem(Item* item)
{
	bool ret = true;

	UnequipItem(item->category);

	if (item->category == ItemCategory::ARMOR)
	{
		armorItem = (Item*)app->entMan->CloneItem(item);
		SetStatsFromItem(armorItem->stats, true);
	}
	else if (item->category == ItemCategory::WEAPON)
	{
		weaponItem = (Item*)app->entMan->CloneItem(item);
		SetStatsFromItem(weaponItem->stats, true);
	}
	else if (item->category == ItemCategory::NECKLACE)
	{
		necklaceItem = (Item*)app->entMan->CloneItem(item);
		SetStatsFromItem(necklaceItem->stats, true);
	}
	else
	{
		ret = false;
	}

	return ret;
}
bool Capybara::UnequipItem(ItemCategory category)
{
	
	if (category == ItemCategory::ARMOR)
	{
		if (armorItem)
		{
			SetStatsFromItem(armorItem->stats, false);
			app->entMan->inventory->AddItem(armorItem,1);
			armorItem = nullptr;
		}
	}
	if (category == ItemCategory::WEAPON)
	{
		if (weaponItem)
		{
			SetStatsFromItem(weaponItem->stats, false);
			app->entMan->inventory->AddItem(weaponItem,1);
			weaponItem = nullptr;
		}
	}
	if (category == ItemCategory::NECKLACE)
	{
		if (necklaceItem)
		{
			SetStatsFromItem(necklaceItem->stats, false);
			app->entMan->inventory->AddItem(necklaceItem,1);
			necklaceItem = nullptr;
		}
	}
	return true;
}