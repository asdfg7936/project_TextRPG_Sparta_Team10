#pragma once
#include "Monster.h"

class Character;	// 전방선언

class Goblin : public Monster {
public:
	Goblin(const Character& character);
	std::string mGetName() const override { return name; }
	int mGetMaxHealth() const override { return maxHealth; }
	int mGetHealth() const override { return health; }
	int mGetAttack() const override { return attack; }
	int mGetExp() const override { return exp; }
	void mTakeDamage(int damage);
};