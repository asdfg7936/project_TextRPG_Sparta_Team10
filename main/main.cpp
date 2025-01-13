#include <iostream>
#include "GameManager.h"

int main()
{
    // Set
    GameManager* GM = GameManager::GetInstance();

    // Init
    {

    }

    // Loop
    {

    }

    // Render
    {

    }
    
    // Log Test
    GM->Log("Hello");

    // End
    GameManager::DestroyInstance();

    return 0;
}
