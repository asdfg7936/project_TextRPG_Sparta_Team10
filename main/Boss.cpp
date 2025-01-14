#include "Boss.h"
#include <string>

Boss::Boss(int level)
	:Monster(level,
		"��ũ ����",
		(rand() % (level * 11)) + (level * 20),	//  ü��
		(rand() % (level * 6)) + (level * 5),		//  ����
		level * 17)												// ����ġ
{
}

void Boss::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}
