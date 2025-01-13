
#include <iostream>
#include "GameManager.h"
#include "FileReaderManager.h"

int main()
{
    // Manager Set
    GameManager* GM = GameManager::GetInstance();

    GM->Init();         // Init
    GM->Progress();     // Update
    
    // Manager Destroy
    GameManager::DestroyInstance();
    FileReaderManager::DestroyInstance();

    return 0;
}
