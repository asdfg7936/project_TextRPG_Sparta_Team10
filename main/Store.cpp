#include "Store.h"

#include "Item.h"
#include "HealthPotion.h"
#include "StrangePotion.h"

#include "../Character/Character.h"

/// <summary>
/// 물약가격
/// 
/// 체력 물약 : 80 
/// 이상한 물약 : 100
/// 
/// 팔때는 원금의 60%
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
	// 1번 : 체력 물약 , 2번 : 이상한 물약
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
	// 1번 : 체력 물약 , 2번 : 이상한 물약
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
