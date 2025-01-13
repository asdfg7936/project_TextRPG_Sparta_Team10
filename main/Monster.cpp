#include "Monster.h"

/*
Monster::Monster(std::string name, int health, int attack, int exp)
	: name(name), health(health), attack(attack), exp(exp) {}
*/

Monster::Monster(int level, std::string name, int maxHealth, int attack, int exp)
	: level(level), name(name), health(maxHealth), attack(attack), exp(exp) {}
