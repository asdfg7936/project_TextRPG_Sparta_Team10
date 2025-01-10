#pragma once
#include "Monster.h"

class Goblin : public Monster {
public:
	Goblin(int level);
	std::string GetName() const override { return name; }
	int GetHealth() const override { return health; }
	int GetAttack() const override { return attack; }
	int GetExp() const override { return exp; }
	void TakeDamage(int damage) override;
};