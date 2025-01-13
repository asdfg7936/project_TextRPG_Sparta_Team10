#include "Orc.h"
#include <cstdlib>
#include "../Character/Character.h"

Orc::Orc(const Character& character)
	:Monster(character.getLevel(),
		"오크", //이름
<<<<<<< Updated upstream
		(rand() % (character.getLevel() * 11)) + (character.getLevel() * 20), //체력
		(rand() % (character.getLevel() * 6)) + (character.getLevel() * 5), //공격
		character.getLevel() * 15 //경험치
=======
		(rand() % (level * 11)) + (level * 20), //체력
		(rand() % (level * 6)) + (level * 5), //공격
		level * 20 //경험치
>>>>>>> Stashed changes
	) {}

void Orc::TakeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}