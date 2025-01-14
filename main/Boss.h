#pragma once
#include "Monster.h"

class Boss : public Monster {
public:
	Boss(int level);
	std::string mGetName() const override { return name; }
	int mGetMaxHealth() const override { return maxHealth; }
	int mGetHealth() const override { return health; }
	int mGetAttack() const override { return attack; }
	int mGetExp() const override { return exp; }
	void mTakeDamage(int damage);
};