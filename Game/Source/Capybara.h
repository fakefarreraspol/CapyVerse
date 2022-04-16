#ifndef __CAPYBARA_H__
#define __CAPYBARA_H__

#include "Entity.h"

struct CapybaraStats
{
	int hp = 1;
	int mp = 1;
	int strenght = 1;
	int speed = 1;
	int armor = 1;
	int intelligence = 1;
};

enum class CapybaraTarget 
{
	NONE = -1,
	HIMSELF,
	ALLIES,
	ENEMIES
};


enum class CapybaraType
{
	NONE = -1,
	TANK,
	DPS,
	SUPP
};

enum class CapybaraStatus
{
	NONE = -1,
	POISONED,
	SLEEP,
	BLEED,
	BLOATED,
	STUNED,
	TAUNTED,
	DEFENSIVE,
	RAGE,
	CLEVER
};

class Capybara : public Entity
{
public:
	//Contructor and destructor
	Capybara(CapybaraType capybaraType, uint32 id, iPoint position, const char* name);
	~Capybara();

	//Base functions
	bool Update(float dt);
	bool Draw(Render* render);

	//Getters
	int& GetHealth();
	int& GetMaxHealth();
	int& GetMana();
	int& GetMaxMana();
	int& GetDamage();
	int& GetArmor();
	int& GetLVL();
	int& GetXP();
	int& GetNextXP();
	CapybaraType& GetType();
	CapybaraStats& GetStats();
	CapybaraStatus& GetStatus();
	CapybaraTarget& GetTarget();

	//Combat functions
	void Damage(int value);
	void Heal(int value);
	void RestoreMana(int value);
	virtual bool UseAbility(Capybara* target);
	void Attack(Capybara* target);
	void SetStatus(CapybaraStatus status);
	void SetAttack(bool isAbleToAttac); //Sets the capy canAttack to true
	bool CanAttack();

	void UpdateStatus();

	//XP functions
	void LevelUp();
	void AddXp(int value);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	void SetCombat(bool value);

protected:
	//Update the stats by the lvl
	void UpdateStats();
	//Initialize all the stats and update them
	void InitStats();
protected:
	//Capybara stats
	CapybaraStats capybaraStats;

	//Health variables
	int health;		//The current health
	int maxHealth;	//The maximun health 
	int healthXLvl;	//The amount of health that every hp lvl gives

	//Damage variables
	int damage;		//The amount of damage by the strenght stat 
	int damageXLvl; //The amount of damage that every strength lvl gives

	//Armor variables
	int armor;		//The amount of armor by the armor stat
	int armorXLvl;	//The amount of armor that every armor lvl gives

	//Mana variables
	int mana;		//The current mana
	int maxMana;	//The maximun mana
	int manaXLvl;	//The amount of mana that every mp lvl gives

	//XP variables
	int xp = 0;		//Current capy xp points
	int level;		//Capybara lvl
	int xpNext;		//Xp points for the next level

	//Combat variables
	bool isCombat = false;
	bool canAttack = true;

	CapybaraType capybaraType = CapybaraType::NONE;			//The capybara type
	CapybaraStatus capybaraStatus = CapybaraStatus::NONE;	//The current status of the capybara
	int statusCounter = 0;									//To remove status and apply them
	CapybaraTarget capybaraTarget = CapybaraTarget::NONE;	//The type of target of the ability
};

#endif // __CAPYBARA_H__
