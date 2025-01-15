
#include <iostream>
#include "GameManager.h"
#include "FileReaderManager.h"

int main()
{
    // Manager Set
    GameManager* GM = GameManager::GetInstance();

    // GameLogic
    GM->Init();         // Init
    GM->Progress();     // Update
    GM->Destroy();      // Clean
    
    // Manager Destroy
    FileReaderManager::DestroyInstance();

    return 0;
}
