#include "StrangePotion.h"
#include "../Character/Character.h"

StrangePotion::StrangePotion()
{
	name = "Strange Potion";
	price = 100;
}

std::string StrangePotion::getName()
{
	return name;
}

int StrangePotion::getPrice()
{
	return price;
}

void StrangePotion::use(Character* character)
{
	Item::use(character);

	std::cout << "������ ���� ���!" << std::endl;

	int probability = rand() % 100;
	if (probability < 40)
	{
		std::cout << "�ƹ� �ϵ� �Ͼ�� �ʾҽ��ϴ�." << std::endl;
	}
	else if (probability < 70)
	{
		character->setAttack(character->getAttack() + 10);
		std::cout << "���ݷ��� 10 ����߽��ϴ�." << std::endl;
	}
	else
	{
		character->setMaxHealth(character->getMaxhealth() + 50);
		std::cout << "�ִ� ü���� 50 ����߽��ϴ�." << std::endl;
	}

	std::cout << "\n";
}
