#include "Orc.h"
#include <cstdlib>

Orc::Orc(int level)
	:Monster(
		"Orc", //이름
		(rand() % (level * 20)) + (level * 30), //체력
		(rand() % (level * 5)) + (level * 10), //공격
		level * 15 //경험치
	) {}

void Orc::TakeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}