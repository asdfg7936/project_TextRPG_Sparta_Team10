#include "Orc.h"
#include <cstdlib>
#include "../Character/Character.h"

Orc::Orc(const Character& character)
	:Monster(character.getLevel(),
		"오크", //이름
		(rand() % (character.getLevel() * 11)) + (character.getLevel() * 20), //체력
		(rand() % (character.getLevel() * 6)) + (character.getLevel() * 5), //공격
		character.getLevel() * 20 //경험치
	) {}

void Orc::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}