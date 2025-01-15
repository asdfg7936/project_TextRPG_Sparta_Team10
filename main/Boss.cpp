#include "Boss.h"
#include <string>


Boss::Boss(int level)
	:Monster(level,
		"��ũ ����",
		4000, 150, 0)
{
}

void Boss::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}