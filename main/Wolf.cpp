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

void Wolf::TakeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}