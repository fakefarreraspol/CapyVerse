#include "Items.h"


void HpPotion::Use(Capybara* capy)
{
	int hp = capy->GetMaxHealth() * 0.3;
	capy->Heal(hp);
	beingUsed = false;
}

void MpPotion::Use(Capybara* capy)
{
	int mp = capy->GetMaxMana() * 0.3;
	capy->RestoreMana(mp);
	beingUsed = false;
}

void Revive::Use(Capybara* capy)
{
	int hp = capy->GetMaxHealth();
	capy->Heal(hp);
	beingUsed = false;
}

void Antidote::Use(Capybara* capy)
{
	capy->SetStatus(CapybaraStatus::NONE);
	beingUsed = false;
}

void ElixirPotion:: Use(Capybara* capy)
{
	capy->Heal(capy->GetMaxHealth() * 0.3);
	capy->RestoreMana(capy->GetMaxMana() * 0.3);
	beingUsed = false;
}

void Spinach::Use(Capybara* capy)
{
	capy->SetStatsFromItem(stats, true);
	beingUsed = true;
}

void Orange::Use(Capybara* capy)
{
	capy->SetStatsFromItem(stats, true);
	beingUsed = true;
}

void Spid::Use(Capybara* capy)
{
	capy->SetStatsFromItem(stats, true);
	beingUsed = true;
}