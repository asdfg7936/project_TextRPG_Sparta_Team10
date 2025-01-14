#include "Troll.h"
#include <cstdlib>

Troll::Troll(int level)
	:Monster(level,
		"Æ®·Ñ",
		(rand() % (level * 11)) + (level * 20),
		(rand() % (level * 6)) + (level * 5),
		level * 23
	) {}

void Troll::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}