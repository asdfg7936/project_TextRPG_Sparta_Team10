#pragma once
#include "Monster.h"


class Boss : public Monster {
public:
	Boss(int level);

	inline std::string mGetName() const override { return name; }
	inline int mGetMaxHealth() const override { return maxHealth; }
	inline int mGetHealth() const override { return health; }
	inline int mGetAttack() const override { return attack; }
	inline int mGetExp() const override { return exp; }
	inline int mGetLevel() const override { return level; }

	void mTakeDamage(int damage);

	void SoundEffect(float per);

private:
	bool bMeet;	// 조우, 50, 20, 주을때
	bool bHpHalf;
	bool bAlmostDeath;
	bool bDeath;
};