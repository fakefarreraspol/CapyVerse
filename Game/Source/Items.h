#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "Item.h"
#include "Entity.h"
#include "Capybara.h"
#include "SString.h"

//CONSUMABLES

class HpPotion : public Item
{
public:
	HpPotion(uint32 id, iPoint bounds, const char* name) :Item(id, bounds, name, ItemType::HP_POTION){
		description.Create("30/100 of maxHP");
		category = ItemCategory::CONSUMABLE;
		this->price = 10;
	}
	~HpPotion() {}
	void Use(Capybara* capy);
};

class MpPotion : public Item
{
public:
	MpPotion(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::MP_POTION) {
		description.Create("+30/100 HP of maxMP");
		category = ItemCategory::CONSUMABLE;
		this->price = 10;
	}

	~MpPotion() {}

	void Use(Capybara* capy);
};


class Revive : public Item
{
public:
	Revive(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::REVIVE) {
		description.Create("Revive a capybara");
		category = ItemCategory::CONSUMABLE;
		this->price = 10;
	}
	~Revive() {}

	void Use(Capybara* capy);
};

class Antidote : public Item
{
public:
	Antidote(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::ANTIDOTE) {
		description.Create("Remove negative stats");
		category = ItemCategory::CONSUMABLE;
		this->price = 10;
	}
	~Antidote() {}

	void Use(Capybara* capy);
};

class ElixirPotion : public Item
{
public:
	ElixirPotion(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::ELIXIR_POTION) {
		description.Create("+30% HP and MP of maximum capacity");
		category = ItemCategory::CONSUMABLE;
		this->price = 10;
	}

	~ElixirPotion() {}

	void Use(Capybara* capy);
};

class Spinach : public Item
{
public:
	Spinach	(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::SPINACH) {
		description.Create("Increases strengt during combat");
		category = ItemCategory::CONSUMABLE;
		stats = { 0,0,2,0,0,0 };
		this->price = 10;
	}
	~Spinach() {}

	void Use(Capybara* capy);
};

class Orange : public Item
{
public:
	Orange(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::ORANGE) {
		description.Create("Increases intelligence during combat");
		category = ItemCategory::CONSUMABLE;
		stats = { 0,0,0,0,0,2 };
		this->price = 10;
	}
	~Orange() {}

	void Use(Capybara* capy);
};

class Spid : public Item
{
public:
	Spid(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::SPID) {
		description.Create("Increases speed during combat");
		category = ItemCategory::CONSUMABLE;
		stats = { 0,0,0,2,0,0 };
		this->price = 10;
	}
	~Spid() {} 

	void Use(Capybara* capy);
};



// EQUIPMENT

class FreeRunersArmor : public Item
{
public:
	FreeRunersArmor(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::FREERUNERS_ARMOR)
	{
		description.Create("Light armor that gives agility");
		category = ItemCategory::ARMOR;
		stats = { 0 };
		stats.speed = 3;
		this->price = 10;
	}
	~FreeRunersArmor();
};

class BowSpellDrinker : public Item
{
public:
	BowSpellDrinker(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::BOW_SPELLDRINKER)
	{
		description.Create("A bow");
		category = ItemCategory::WEAPON;
		stats = { 0 };
		stats.strenght = 2;
		this->price = 10;
	}
	~BowSpellDrinker();

};

class ArmorVulnerability : public Item
{
public:
	ArmorVulnerability(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::ARMOR_VULNERABILITY)
	{
		description.Create("Heavy armor");
		category = ItemCategory::ARMOR;
		stats = { -1,0,3,0,0,0 };
		this->price = 10;
	}
	~ArmorVulnerability();


};

class ScholarNecklace : public Item
{
public:
	ScholarNecklace(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::SCHOLAR_NECKLACE)
	{
		description.Create("An ideal necklace for SUPP");
		category = ItemCategory::NECKLACE;
		stats = { 0,1,0,0,0,2 };
		this->price = 10;
	}
	~ScholarNecklace();

};

class HeavySword : public Item
{
public:
	HeavySword(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::HEAVY_SWORD)
	{
		description.Create("Powerful but heavy sword");
		category = ItemCategory::WEAPON;
		stats = { 0,0,3,-1,0,0 };
		this->price = 10;
	}
	~HeavySword();

};

class BambuArmor : public Item
{
public:
	BambuArmor(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::BAMBU_ARMOR)
	{
		description.Create("Light armor");
		category = ItemCategory::ARMOR;
		stats = { 1,0,0,0,1,0 };
		this->price = 10;
	}
	~BambuArmor();

};

class MysteryArmor : public Item
{
public:
	MysteryArmor(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::MYSTERY_ARMOR)
	{
		description.Create("This armor is extremely protective");
		category = ItemCategory::ARMOR;
		stats = { 2,0,0,0,3,0 };
		this->price = 10;
	}
	~MysteryArmor();

};

class HealthNecklace : public Item
{
public:
	HealthNecklace(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::HEALTH_NECKLACE)
	{
		description.Create("Gives the user vitality");
		category = ItemCategory::NECKLACE;
		stats = { 1,0,0,0,1,0 };
		this->price = 10;
	}
	~HealthNecklace();

};

class PowerNecklace : public Item
{
public:
	PowerNecklace(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::POWER_NECKLACE)
	{
		description.Create("An ideal necklace for SUPP");
		category = ItemCategory::NECKLACE;
		stats = { 0,0,2,0,0,0 };
		this->price = 10;
	}
	~PowerNecklace();

};

class LightNecklace : public Item
{
public:
	LightNecklace(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::LIGHT_NECKLACE)
	{
		description.Create("An ideal necklace for SUPP");
		category = ItemCategory::NECKLACE;
		stats = { 0,0,0,2,0,0 };
		this->price = 10;
	}
	~LightNecklace();

};


#endif // !__ITEMS_H__