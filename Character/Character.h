#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Character {
private:
    string name;
    static Character* instance;
    int level;
    int health;
    int maxhealth;
    int attack;
    int experience;
    int gold;
    //vector<item> inventory;

    Character(string name);

public:
    static Character* getInstance(string name = "");
    void displayStatus();
    void levelUp();
    void useItem(int index);
};
