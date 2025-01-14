#include "Boss.h"
#include <string>

Boss::Boss(int level)
	:Monster(level,
		"오크 족장",
		(rand() % (level * 11)) + (level * 20),	//  체력
		(rand() % (level * 6)) + (level * 5),		//  공격
		level * 17)												// 경험치
{
}

void Boss::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}
