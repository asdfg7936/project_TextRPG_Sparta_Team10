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
    int maxhealth;
    int attack;
    int experience;
    int experienceToNestLevel;
    int gold;
    //vector<item> inventory;

    Character(string name);

    Character(const Character&) = delete;
    Character& operator = (const Character&) = delete;

public:
    static Character* getInstance(string name = "");
    void displayStatus();
    void levelUp();
    void useItem(int index);
    int getMaxhealth();
    int getLevel();
    void setHealth(int health);
};
