#pragma once
#include <string>

//몬스터 클래스
class Monster {
protected:
    int level;
    std::string name;
    int maxHealth;
    int health;
    int attack;
    int exp;

public:
    Monster(int level, std::string name, int maxHealth, int attack, int exp);
    virtual ~Monster() {}

    virtual std::string mGetName() const = 0;
    virtual int mGetMaxHealth() const = 0;
    virtual int mGetHealth() const = 0;
    virtual int mGetAttack() const = 0;
    virtual int mGetExp() const = 0;
    virtual int mGetLevel() const = 0;
    virtual void mTakeDamage(int damage) = 0;
    virtual void mDisplayStatus();
};