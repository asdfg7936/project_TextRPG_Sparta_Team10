#pragma once
#include "Monster.h"

class Orc : public Monster {

public:
	Orc(int level);
	std::string getName() const override { return name; }
	int GetHealth() const override { return health; }
	int GetAttack() const override { return attack; }
	int GetExp() const override { return exp; }
	void TakeDamage(int damage) override;
};
// ¾Æ¾Æ