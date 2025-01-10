#include "AttackBoost.h"

AttackBoost::AttackBoost()
{
	name = "Attack Boost Potion";
}

std::string AttackBoost::getName()
{
	return name;
}

void AttackBoost::use(Character* character)
{
	Item::use(character);

	// ?
}
