
#include <iostream>
#include "GameManager.h"
#include "FileReaderManager.h"

/// <summary>
/// 
/// �÷��̾� �̸� : English Only!!
/// 
/// </summary>
int main()
{
    // GameLogic
    GM->Init();         // Init
    GM->Progress();     // Update
    GM->Destroy();      // Clean
    
    // Manager Destroy
    FileReaderManager::DestroyInstance();

    return 0;
}
