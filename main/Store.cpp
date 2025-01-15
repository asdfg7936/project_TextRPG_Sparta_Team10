#include "Store.h"

#include "Item.h"
#include "HealthPotion.h"
#include "StrangePotion.h"

#include "../Character/Character.h"

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
	int gold = player->getGold();
	
	switch (idx)
	{
	case EItem::Heal:

		break;
	case EItem::Strange:

		break;
	default:
		__noop;
	}

}

void Store::sellStuff(int idx)
{
	// 1�� : ü�� ���� , 2�� : �̻��� ����
	int gold = player->getGold();

	switch (idx)
	{
	case EItem::Heal:

		break;
	case EItem::Strange:

		break;
	default:
		__noop;
	}
}
