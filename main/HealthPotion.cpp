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

	std::cout << "ȸ�� ���� ���!" << std::endl;

	character->setHealth(character->getHealth() + (character->getMaxhealth() * 0.4));

	std::cout << "ü���� " << character->getMaxhealth() * 0.4 << "��ŭ ȸ���Ǿ����ϴ�." << std::endl;
}
