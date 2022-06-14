#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"

class Capybara;

struct ItemStats
{
	int hp = 1;
	int mp = 1;
	int strenght = 1;
	int speed = 1;
	int armor = 1;
	int intelligence = 1;
};

enum ItemType
{
	NONE = -1,
	HP_POTION,
	MP_POTION,
	REVIVE,
	ANTIDOTE,
	ELIXIR_POTION,
	SPINACH,
	ORANGE,
	SPID,

	FREERUNERS_ARMOR,
	BOW_SPELLDRINKER,
	ARMOR_VULNERABILITY,
	SCHOLAR_NECKLACE,
	HEAVY_SWORD,
	BAMBU_ARMOR,
	MYSTERY_ARMOR,
	HEALTH_NECKLACE,
	POWER_NECKLACE,
	LIGHT_NECKLACE
};

enum class ItemCategory
{
	NONE=-1,
	OBJECT,
	CONSUMABLE,
	ARMOR,
	WEAPON,
	NECKLACE
};

class Item : public Entity
{
public:
	
	Item(uint32 id, iPoint bounds, const char* name, ItemType type) : Entity(EntityType::ITEM, id, name, bounds), itemType(type)
	{
	}
	~Item() {}

	virtual bool Update(float dt) { return true; }

	virtual bool Draw(Render* render) { return true; }

	virtual bool CleanUp() { return true; }
	
	virtual void Use(Capybara* capy) {}
	
	virtual void Disable() {}

public:
	ItemType itemType = ItemType::NONE;
	bool beingUsed = false;   
	SString description;
	ItemStats stats;
	ItemCategory category;
};


#endif // __ITEM_H__