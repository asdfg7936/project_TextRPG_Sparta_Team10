#pragma once
#include "Monster.h"

class Character;

class Wolf : public Monster {
public:
	Wolf(const Character& character);
	std::string GetName() const override { return name; }
	int GetHealth() const override { return health; }
	int GetAttack() const override { return attack; }
	int GetExp() const override { return exp; }
	void TakeDamage(int damage) override;
};