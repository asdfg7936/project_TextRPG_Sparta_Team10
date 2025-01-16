#pragma once
#include <iostream>
#include <fstream>
#include <windows.h> // Windows API ���

#define GM GameManager::GetInstance()

class Monster;

class GameManager
{
private:
	int wolfCount = 0;
	int goblinCount = 0;
	int orcCount = 0;
	int trollCount = 0;
	static GameManager* instance;

	GameManager()
	{
		//std::cout << "[ Create Game Manager ]" << std::endl;
	}
	~GameManager() {}

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:
	static GameManager* GetInstance() 
	{
 		if (nullptr == instance)
		{
			instance = new GameManager();
		}
		return instance;
	}
	static void DestroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
			//std::cout << "[ Delete Game Manager ]" << std::endl;
		}
	}

// Game Logic
public:
	void Init();		// �ʱ�ȭ
	void Progress();	// ���� ����
	bool Update();		// ���� ������ ������Ʈ
	void Destroy();		// ������ ����

// Function
public:
	static void setConsoleColor(int color) 
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
		SetConsoleTextAttribute(hConsole, color);         // ���� ����
	}
	void SetGameEndCondition(bool flag) { bBossDeath = flag; }

private:
	bool bBossDeath = false;

	Monster* GenMonster(int playerLevel);
	void displayKillCounts() const;	// ���� óġ ���

	void SetPlayerCharacter();	// �ʱ� �÷��̾� �̸� ���� �� ����
	void Intro();

// Player Input
private:
	int SelectOption();
	void SelectStore();
	void SelectStatus();
	void SelectInventory();
	Monster* SelectBattle();
	void BattleReward(Monster* genMonster);
	bool SelectEndGame();

};
