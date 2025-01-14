#include "Wolf.h"
#include <cstdlib>

Wolf::Wolf(int level)
	:Monster(level,
		"����",
		(rand() % (level * 11)) + (level * 20),
		(rand() % (level * 6)) + (level * 5),
		level * 15
	) {}

void Wolf::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}