#include <iostream>
#include "GameManager.h"

int main()
{
    GameManager* GM = GameManager::GetInstance();   // Set
    
    GM->Init();         // Init
    GM->Progress();     // Update
        
    GameManager::DestroyInstance(); // End

    return 0;
}
