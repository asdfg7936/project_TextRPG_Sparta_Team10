#pragma once
#include <string>

class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int exp;

public:
    Monster(std::string name, int health, int attack);
    virtual ~Monster() {}

    virtual std::string GetName() const = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual int GetExp() const = 0;
    virtual void TakeDamage(int damage) = 0;
};