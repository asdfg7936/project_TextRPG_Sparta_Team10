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

    Character(string name) {
        this->name = name;
        this->level = 1;
        this->attack = 30;
        this->health = 200;
        this->maxhealth = 200;
        this->experience = 0;
        this->gold = 0;
    }

public:
    static Character* getInstance(string name = "") {
        if (instance == nullptr) {
            instance = new Character(name);
        }
        return instance;
    }
    void displayStatus(){

    }
    void levelUp() {
        this->level++;
    }
    void useItem(int index) {

    }
};

int main() {
	
}