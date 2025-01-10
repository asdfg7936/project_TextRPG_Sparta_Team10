#pragma once
#include "Item.h"

class Gold :
	public Item
{
public:
	Gold();

public:
	virtual std::string getName();
	virtual void use(Character* character);
};

