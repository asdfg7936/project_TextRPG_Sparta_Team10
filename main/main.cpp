
#include <iostream>
#include "GameManager.h"
#include "FileReaderManager.h"

int main()
{
    // Manager Set
    GameManager* GM = GameManager::GetInstance();
    FileReaderManager* FRM = FileReaderManager::GetInstance();

    FRM->OpenFile("../test.txt");
    FRM->CloseFile();

    GM->Init();         // Init
    GM->Progress();     // Update
    
    // Manager Destroy
    GameManager::DestroyInstance();
    FileReaderManager::DestroyInstance();

    return 0;
}
