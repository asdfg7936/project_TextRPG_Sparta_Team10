#include "HealthPotion.h"


HealthPotion::HealthPotion()
{
	name = "Health Potion";
}

std::string HealthPotion::getName()
{
	return name;
}

void HealthPotion::use(Character* character)
{
	Item::use(character);

	// ?
}
