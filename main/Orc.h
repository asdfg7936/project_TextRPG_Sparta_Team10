#pragma once
#include "Monster.h"

class Orc : public Monster {
public:
	Orc(int level);
	std::string mGetName() const override { return name; }
	int mGetMaxHealth() const override { return maxHealth; }
	int mGetHealth() const override { return health; }
	int mGetAttack() const override { return attack; }
	int mGetExp() const override { return exp; }
	void mTakeDamage(int damage) override;
};