#pragma once
#include <string>
#include "../Character/Character.h"

class Character;

class Item
{
protected:
	int quantity = 0;
	std::string name = "";

public:
	virtual std::string getName() = 0;
	virtual void use(Character* character);

public:
	int getQuantity();
};

