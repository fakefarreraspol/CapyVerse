#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "Item.h"

//CONSUMABLES

class HpPotion : public Item
{
public:
	HpPotion(uint32 id, iPoint bounds, const char name) :Item(id, bounds, name, ItemType::HP_POTION) {}
	~HpPotion() {}
	void Use(Capybara* capy)
	{
		if (active == true)
			capy->capybaraStats.hp += capy->capybaraStats.hp * 0.3;
		active = false;
	}
};

class MpPotion : public Item
{
public:
	MpPotion(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::MP_POTION) {}

	~MpPotion() {}

	void Use(Capybara* capy)
	{
		if (active == true)
			capy->capybaraStats.mp += capy->capybaraStats.mp * 0.3;
		active = false;
	}
};


class Revive : public Item
{
public:
	Revive(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::REVIVE) {}
	~Revive() {}

	void Use(Capybara* capy)
	{
		if (capy->active == true)
			capy->capybaraStats.hp = capy->GetMaxHealth();
		active = false;
	}

};

class Antidote : public Item
{
public:
	Antidote(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::ANTIDOTE) {}
	~Antidote() {}

	void Use(Capybara* capy)
	{
		capy->SetStatus(CapybaraStatus::NONE);
	}
};

class ElixirPotion : public Item
{
public:
	ElixirPotion(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::ELIXIR_POTION) {}

	~ElixirPotion() {}

	void Use(Capybara* capy)
	{
		if (active == true)
		{
			capy->capybaraStats.mp += capy->capybaraStats.mp * 0.3;
			capy->capybaraStats.mp += capy->capybaraStats.mp * 0.3;
		}
		active = false;
	}
};

class Spinach : public Item
{
public:
	Spinach	(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::SPINACH) {}
	~Spinach() {}

	void Use(Capybara* capy)
	{
		capy->capybaraStats.strenght += 2;
		beingUsed = true;
		this->capy = capy;
	}
	bool Update(float dt)
	{
		if (beingUsed && !capy->IsOnCombat())
		{
			capy->capybaraStats.strenght -= 2;
			capy = nullptr;
			beingUsed = false;
		}
		return true;
	}
};

class Orange : public Item
{
public:
	Orange(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::ORANGE) {}
	~Orange() {}

	void Use(Capybara* capy)
	{
		capy->capybaraStats.intelligence += 2;
		beingUsed = true;
		this->capy = capy;
	}
	bool Update(float dt)
	{
		if (beingUsed && !capy->IsOnCombat())
		{
			capy->capybaraStats.intelligence -= 2;
			capy = nullptr;
			beingUsed = false;
		}
		return true;
	}
};

class Spid : public Item
{
public:
	Spid(uint32 id, iPoint bounds, const char* name) : Item(id, bounds, name, ItemType::SPID) {}
	~Spid() {} 

	void Use(Capybara* capy)
	{
		capy->capybaraStats.speed += 2;
		beingUsed = true;
		this->capy = capy;
	}
	bool Update(float dt)
	{
		if (beingUsed && !capy->IsOnCombat())
		{
			capy->capybaraStats.speed -= 2;
			capy = nullptr;
			beingUsed = false;
		}
		return true;
	}
};



// EQUIPMENT

class FreeRunersArmor : public Item
{
public:
	FreeRunersArmor(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::FREERUNERS_ARMOR)
	{

	}
	~FreeRunersArmor();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.speed += 3;
	}

	void UnPick()
	{
		capy->capybaraStats.speed -= 3;
		capy = nullptr;
	}
};

class BowSpellDrinker : public Item
{
public:
	BowSpellDrinker(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::BOW_SPELLDRINKER)
	{

	}
	~BowSpellDrinker();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.strenght += 2;
	}

	void UnPick()
	{
		capy->capybaraStats.strenght -= 2;
		capy = nullptr;
	}
};

class ArmorVulnerability : public Item
{
public:
	ArmorVulnerability(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::ARMOR_VULNERABILITY)
	{

	}
	~ArmorVulnerability();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.strenght += 3;
		this->capy->capybaraStats.hp--;
	}

	void UnPick()
	{
		capy->capybaraStats.strenght -= 3;
		capy->capybaraStats.hp++;
		capy = nullptr;
	}
};

class ScholarNecklace : public Item
{
public:
	ScholarNecklace(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::SCHOLAR_NECKLACE)
	{

	}
	~ScholarNecklace();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.intelligence += 2;
		this->capy->capybaraStats.mp++;
	}

	void UnPick()
	{
		capy->capybaraStats.intelligence -= 2;
		capy = nullptr;
	}
};

class HeavySword : public Item
{
public:
	HeavySword(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::HEAVY_SWORD)
	{

	}
	~HeavySword();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.strenght += 3;
		this->capy->capybaraStats.speed--;
	}

	void UnPick()
	{
		this->capy->capybaraStats.strenght -= 3;
		this->capy->capybaraStats.speed++;
		capy = nullptr;
	}
};

class BambuArmor : public Item
{
public:
	BambuArmor(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::BAMBU_ARMOR)
	{

	}
	~BambuArmor();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.armor++;
		this->capy->capybaraStats.hp++;
	}

	void UnPick()
	{
		this->capy->capybaraStats.armor--;
		this->capy->capybaraStats.hp--;
		if (this->capy->capybaraStats.hp >= 0)
			this->capy->capybaraStats.hp = 1;
		capy = nullptr;
	}
};

class MysteryArmor : public Item
{
public:
	MysteryArmor(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::MYSTERY_ARMOR)
	{

	}
	~MysteryArmor();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.armor += 3;
		this->capy->capybaraStats.hp += 2;
	}

	void UnPick()
	{
		this->capy->capybaraStats.armor -= 3;
		this->capy->capybaraStats.hp -= 2;
		if (this->capy->capybaraStats.hp >= 0)
			this->capy->capybaraStats.hp = 1;

		capy = nullptr;
	}
};

class HealthNecklace : public Item
{
public:
	HealthNecklace(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::HEALTH_NECKLACE)
	{

	}
	~HealthNecklace();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.armor += 1;
		this->capy->capybaraStats.hp += 1;
	}

	void UnPick()
	{
		this->capy->capybaraStats.armor -= 1;
		this->capy->capybaraStats.hp -= 1;
		if (this->capy->capybaraStats.hp >= 0)
			this->capy->capybaraStats.hp = 1;

		capy = nullptr;
	}
};

class PowerNecklace : public Item
{
public:
	PowerNecklace(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::POWER_NECKLACE)
	{

	}
	~PowerNecklace();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.strenght += 2;
	}

	void UnPick()
	{
		capy->capybaraStats.strenght -= 2;
		capy = nullptr;
	}
};

class LightNecklace : public Item
{
public:
	LightNecklace(uint32 id, iPoint bounds, const char name) : Item(id, bounds, name, ItemType::LIGHT_NECKLACE)
	{

	}
	~LightNecklace();

	void Disable()
	{
		active = false;
	}

	bool GetPicked(Capybara* capy)
	{
		if (capy != nullptr)
			UnPick();

		this->capy = capy;
		this->capy->capybaraStats.speed += 2;
	}

	void UnPick()
	{
		capy->capybaraStats.speed -= 2;
		capy = nullptr;
	}
};


#endif // !__ITEMS_H__