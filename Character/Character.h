#include <iostream>
#include <string>
#include <vector>

/// <summary>
/// 플레이어 사망을 확인할 수 있는 public 함수
/// 반환 값 bool (생존시 true ,  사망시 false)
/// bool IsAlive();
/// </summary>
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

//Character* Charcter::instance = nullptr;
Character* Character::instance = nullptr;   // modify typo_kgh