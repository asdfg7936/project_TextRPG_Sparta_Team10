#include "Orc.h"
#include <cstdlib>

Orc::Orc(int level)
	:Monster(
		"오크", //이름
		(rand() % (level * 11)) + (level * 20), //체력
		(rand() % (level * 6)) + (level * 5), //공격
		level * 15 //경험치
	) {}

void Orc::TakeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}