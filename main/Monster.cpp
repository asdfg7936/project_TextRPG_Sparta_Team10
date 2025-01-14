#include "Monster.h"

Monster::Monster(int level, std::string name, int maxHealth, int attack, int exp)
	: level(level), name(name), maxHealth(maxHealth), attack(attack), exp(exp) {
	health = maxHealth;
}

int Monster::mGetAttack() const
{
	return attack;
}

int Monster::mGetExp() const 
{
	return exp;
}

void Monster::mDisplayStatus()
{
	cout << "- " << name << " -"
	cout << "Level: " << level << endl;
	cout << "Health: " << health << " / " << maxHealth << endl;
	cout << "Attack: " << attack << endl;
}