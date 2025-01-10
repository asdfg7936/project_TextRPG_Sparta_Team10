#include "Gold.h"

Gold::Gold()
{
	name = "Gold";
}

std::string Gold::getName()
{
	return name;
}

void Gold::use(Character* character)
{
	Item::use(character);

	// ?
}
