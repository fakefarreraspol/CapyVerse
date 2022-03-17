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

enum class CapybaraType
{
	NONE = -1,
	TANK,
	DPS,
	SUPP
};

class Capybara : public Entity
{
public:
	//Contructor and destructor
	Capybara(CapybaraType capybaraType);
	~Capybara();

	//Base functions
	bool Update(float dt);
	bool Draw(Render* render);


	//Setters and getters
	int GetHealth();
	int GetMana();
	CapybaraType GetType();
	CapybaraStats GetStats();

	//Combat functions
	void Damage(int damage);
	void Heal(int heal);
	void UseAbility();
	void Attack(Capybara* target);

	void LevelUp();
private:
	//Update the stats by the lvl
	void UpdateStats();
private:
	//Capybara stats
	CapybaraStats capybaraStats;
	
	//Health variables
	int health;
	int maxHealth;
	int healthXLvl;	//The amount of health that every hp lvl gives

	int damage;		//The amount of damage by the strenght stat 
	int damageXLvl; //The amount of damage that every strength lvl gives

	//Mana variables
	int mana;
	int maxMana;
	int manaXLvl;	//The amount of mana that every mp lvl gives

	int xp;			//Current capy xp points
	int lvl;		//Capy lvl
	int xpNext;		//Xp points for the next level

	bool isCombat = false;

	CapybaraType capybaraType = CapybaraType::NONE;
};

#endif // !__CAPYBARA_H__
