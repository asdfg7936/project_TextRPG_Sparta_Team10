#include "Troll.h"
#include <cstdlib>
#include "../Character/Character.h"

Troll::Troll(const Character& character)
	:Monster(character.getLevel(),
		"Æ®·Ñ",
		(rand() % (character.getLevel() * 11)) + (character.getLevel() * 20),
		(rand() % (character.getLevel() * 6)) + (character.getLevel() * 5),
		character.getLevel() * 23
	) {}

void Troll::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}