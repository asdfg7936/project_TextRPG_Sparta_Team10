#include "Troll.h"
#include <cstdlib>

Troll::Troll(int level)
	:Monster(
		"Æ®·Ñ",
		(rand() % (level * 11)) + (level * 20),
		(rand() % (level * 6)) + (level * 5),
		level * 15
	) {}

void Troll::TakeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}
