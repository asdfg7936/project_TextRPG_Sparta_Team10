#pragma once
#include "Monster.h"

class Character;

class Troll : public Monster {
public:
	Troll(const Character& character);
	std::string mGetName() const override { return name; }
	int mGetMaxHealth() const override { return maxHealth; }
	int mGetHealth() const override { return health; }
	int mGetAttack() const override { return attack; }
	int mGetExp() const override { return exp; }
	void mTakeDamage(const Character& character);
};