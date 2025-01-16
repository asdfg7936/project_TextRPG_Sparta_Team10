#include "Store.h"

#include "Item.h"
#include "HealthPotion.h"
#include "StrangePotion.h"

#include "../Character/Character.h"

#include <iostream>

/// <summary>
/// ���డ��
/// 
/// ü�� ���� : 80 
/// �̻��� ���� : 100
/// 
/// �ȶ��� ������ 60%
/// 
/// </summary>

Store::Store()
{
	Character* player = Character::getInstance();

	items.push_back(new HealthPotion());
	items.push_back(new StrangePotion());
}


void Store::buyStuff(int idx)
{
	// 1�� : ü�� ���� , 2�� : �̻��� ����
	Character* player = Character::getInstance();
	int gold = player->getGold();
	Stuff* Item;
	
	switch (idx-1)
	{
	case EItem::Heal:
		if (gold >= 80)
		{
			player->setGold(player->getGold() - 80);
			Item = player->getItem(EItem::Heal);
			Item->ItemQuantity += 1;
			std::cout << "ü�� ������ �����߽��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "\n��尡 �����մϴ�!" << std::endl;
		}
		break;
	case EItem::Strange:
		if (gold >= 100)
		{
			player->setGold(player->getGold() - 100);
			Item = player->getItem(EItem::Strange);
			Item->ItemQuantity += 1;
			std::cout << "ü�� ������ �����߽��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "��尡 �����մϴ�!" << std::endl;
		}
		break;
	default:
		__noop;
	}
	std::cout << std::endl;
}

void Store::sellStuff(int idx)
{
	// 1�� : ü�� ���� , 2�� : �̻��� ����
	Character* player = Character::getInstance();
	int gold = player->getGold();
	Stuff* Item;

	switch (idx-1)
	{
	case EItem::Heal:
		player->setGold(player->getGold() + 48);
		Item = player->getItem(EItem::Heal);
		Item->ItemQuantity -= 1;
		std::cout << "ü�� ������ �Ǹ��߽��ϴ�." << std::endl;
		std::cout << "��尡 48 �����߽��ϴ�." << std::endl;
		break;
	case EItem::Strange:
		player->setGold(player->getGold() + 60);
		Item = player->getItem(EItem::Strange);
		Item->ItemQuantity -= 1;
		std::cout << "������ ������ �Ǹ��߽��ϴ�." << std::endl;
		std::cout << "��尡 60 �����߽��ϴ�." << std::endl;
		break;
	default:
		__noop;
	}
	std::cout << std::endl;
}

void Store::showList()
{
	std::cout << "---------------------����---------------------" << std::endl;
	std::cout << "�Ǹ� ���" << std::endl;
	for (int i = 0; i < items.size(); i++)
	{
		std::cout << i + 1 << " : " << items[i]->getName();
		std::cout << "\n ///// ���� ����: " << items[i]->getPrice() << " ///// �Ǹ� ����: " << items[i]->getPrice()*0.6 << " /////\n" << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << std::endl;
}
