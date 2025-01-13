#include "Wolf.h"
#include <cstdlib>
#include "../Character/Character.h"

Wolf::Wolf(const Character& character)
	:Monster(character.getLevel(),
		"´Á´ë",
		(rand() % (character.getLevel() * 11)) + (character.getLevel() * 20),
		(rand() % (character.getLevel() * 6)) + (character.getLevel() * 5),
		character.getLevel() * 15
	) {}

void Wolf::TakeDamage(const Character& character) {
	health -= character.getAttack;
	if (health < 0) {
		health = 0;
	}
}