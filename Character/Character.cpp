#include "Character.h"

Character* Character::instance = nullptr;

Character::Character(string name)
{
	this->name = name;
	this->level = 1;
	this->attack = 30;
	this->health = 200;
	this->maxHealth = 200;
	this->experience = 0;
	this->experienceToNestLevel = 100;
	this->gold = 0;
}

Character* Character::getInstance(string name)
{
	if (instance == nullptr)
	{
		instance = new Character(name);
	}

	return instance;
}

void Character::displayStatus()
{
	cout << "------------------" << endl;
	cout << "Status" << endl;
	cout << "Level: " << level << endl;
	cout << "Exp: " << experience << " / " << experienceToNestLevel << endl;
	cout << "Health: " << health << " / " << maxHealth << endl;
	cout << "Attack: " << attack << endl;
	cout << "------------------" << endl;
}
void Character::levelUp()
{
	if (level < 10)
	{
		this->level++;
		if (this->experience > this->experienceToNestLevel)
		{
			this->experience -= experienceToNestLevel;
		}	
		this->maxHealth += level * 20;
		this->health = maxHealth;
		this->attack += level * 5;
		this->experienceToNestLevel += experienceToNestLevel * 0.2;

		cout << "------------------" << endl;
		cout << "Level Up!" << endl;
		cout << "------------------" << endl;
		std::cout << endl;
	}
	else
	{
		cout << "------------------" << endl;
		cout << "Alredy Maxlevel!" << endl;
		cout << "------------------" << endl;
	}
}
//void Character::useItem(int index)

int Character::getMaxhealth() const
{
	return this->maxHealth;
}
int Character::getHealth() const
{
	return this->health;
}
void Character::setHealth(int health) 
{
    this->health = health;
}
void Character::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}
bool Character::IsAlive()
{
	if (this->health > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Character::getAttack() const
{
	return this->attack;
}
int Character::getGold() const
{
	return this->gold;
}
void Character::setGold(int gold)
{
	this->gold = gold;
}
void Character::TakeDamage(int damage)
{
	if (this->health - damage > 0)
	{
		this->health -= damage;
	}
	else
	{
		this->health = 0;
	}
}
double Character::getExperience() const
{
	return this->experience;
}
void Character::setAttack(int attack)
{
	this->attack = attack;
}
double Character::getExperienceToNextLevel() const
{
	return this->experienceToNestLevel;
}
string Character::getName() const
{
	return this->name;
}
void Character::setExperience(double experience)
{
	this->experience = experience;
}
int Character::getLevel() const
{
	return this->level;
}


