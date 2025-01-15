#pragma once
#include "Item.h"
#include <string>

class StrangePotion :
	public Item
{
public:
	StrangePotion();

public:
	virtual std::string getName();
	virtual void use(Character* character);
};

