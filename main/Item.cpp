#include "Item.h"
#include "../Character/Character.h"

void Item::use(Character* character)
{
    if (quantity == 0)
    {
        return;
    }
    --quantity;
}

int Item::getQuantity()
{
    return quantity;
}
