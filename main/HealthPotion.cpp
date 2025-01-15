#include "HealthPotion.h"
#include "../Character/Character.h"

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

	std::cout << "회복 물약 사용!" << std::endl;

	character->setHealth(character->getHealth() + (character->getMaxhealth() * 0.4));

	std::cout << "체력이 " << character->getMaxhealth() * 0.4 << "만큼 회복되었습니다." << std::endl;
}
