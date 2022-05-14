#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"
#include "Capybara.h"

enum class ItemType
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

class Item : public Entity
{
public:

	Item(uint32 id, iPoint bounds, const char* name, ItemType type): Entity(EntityType::ITEM,id,name,bounds)
	{
		this->type = type;
	};
	~Item() {};

	virtual bool Update(float dt) { return true; }

	virtual bool Draw(Render* render) { return true; }

	virtual bool CleanUp() { return true; }
	
	virtual bool GetPicked(Capybara* capy) { return true; }

	virtual void UnPick() {}

	virtual void Use(Capybara* capy) {}
	
	virtual void Disable() {}
public:
	ItemType type = ItemType::NONE;
	Capybara* capy = nullptr;
	bool beingUsed = false;   
	SString description;

};


#endif // __ITEM_H__