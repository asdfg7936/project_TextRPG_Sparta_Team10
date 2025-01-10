#pragma once
#include "Item.h"
#include <string>

class AttackBoost :
    public Item
{
public:
	AttackBoost();

public:
	virtual std::string getName();
	virtual void use(Character* character);
};

