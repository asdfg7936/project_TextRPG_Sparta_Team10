#include "Character.h"

Character::Character(string name)
{
	this->name = name;
	this->level = 1;
	this->attack = 30;
	this->health = 200;
	this->maxhealth = 200;
	this->experience = 0;
	this->experienceToNestLevel = 100;
	this->gold = 0;
}

static Character::Character* getInstance(string name = "")
{
	if (instance == nullptr)
	{
		instance = new Character(name);
	}
	return instance;
}
void Character::displayStatus()
{
	cout << "Status" << endl;
	cout << "Level: " << level << endl;
	cout << "Exp: " << experience << " / " <<  << endl;
	cout << "Health: " << health << " / " << endl;
	cout << "Attack: " << attack << endl;
}
void Character::levelUp()
{
	if (level <= 10)
	{
		this->level++;
		this->maxhealth += level * 20;
		this->health = maxhealth;
		this->attack += level * 5;
		this->experienceToNestLevel += experienceToNestLevel * 0.2;

		cout << "Level Up!" << endl;
	}
	else
	{
		cout << "Alredy Maxlevel!" << endl;
	}
}
int Character::getMaxhealth() 
{
    return this->maxhealth;
}
void Character::setHealth(int health) 
{
    this->health = health;
}
int Character::getLevel()
{
	return this->level;
}
void Character::useItem(int index)
{

}
