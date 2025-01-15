#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Character 
{
private:
    string name;
    static Character* instance;
    int level;
    int health;
    int maxHealth;
    int attack;
    double experience;
    double experienceToNestLevel;
    int gold;
    //vector<Stuff> inventory;

    Character(string name);

    Character(const Character&) = delete;
    Character& operator = (const Character&) = delete;

public:
    static Character* getInstance(string name = "");
    void displayStatus();
    void levelUp();
    int getMaxhealth() const;
    int getHealth() const;
    int getLevel() const;
    void setHealth(int health);
    void setMaxHealth(int maxHealth);
    bool IsAlive();
    int getAttack() const;
    int getGold() const;
    void setGold(int gold);
    void TakeDamage(int damage);
    void setExperience(double experience);
    void setAttack(int attack);
    double getExperience() const;
    double getExperienceToNextLevel() const;
    string getName() const;

    // ������
    void usePotion();
};


