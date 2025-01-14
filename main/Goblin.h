#pragma once
#include "Monster.h"

class Goblin : public Monster {
public:
	Goblin(int level);
	std::string mGetName() const override { return name; }
	int mGetMaxHealth() const override { return maxHealth; }
	int mGetHealth() const override { return health; }
	int mGetAttack() const override { return attack; }
	int mGetExp() const override { return exp; }
	void mTakeDamage(int damage);
};