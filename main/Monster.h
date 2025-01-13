#pragma once
#include <string>

//몬스터 클래스
class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int exp;

public:
    Monster(int level, std::string name, int health, int attack, int exp);
    virtual ~Monster() {}

    virtual std::string GetName() const = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual int GetExp() const = 0;
    virtual void TakeDamage(int damage) = 0;
};