#pragma once
#include <iostream>
#include <fstream>

class Monster;

class GameManager
{
private:
	int wolfCount = 0;
	int goblinCount = 0;
	int orcCount = 0;
	int trollCount = 0;
	static GameManager* instance;

	std::ofstream logFile;	// Output File Stream

	GameManager()
	{
		std::cout << "[ Create Game Manager ]" << std::endl;

		logFile.open("../log.txt", std::ios::app); // �α� ���� ���� (append ���)
		if (!logFile.is_open()) {
			throw std::runtime_error("[ Unable to open log file. ]");
		}
		else
		{
			std::cout << "[ Set Log File ]" << std::endl;
		}
	}

	~GameManager() 
	{
		if (logFile.is_open()) {
			logFile.close();
			std::cout << "[ Close Log File ]" << std::endl;
		}
	}

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
			std::cout << "[ Delete Game Manager ]" << std::endl;
		}
	}

	void displayKillCounts() const {
		std::cout << std::endl;
		std::cout << "------------------" << std::endl;
		std::cout << "������� ���� ���� ��" << std::endl;
		std::cout << "���� : " << wolfCount << std::endl;
		std::cout << "��� : " << goblinCount << std::endl;
		std::cout << "��ũ : " << orcCount << std::endl;
		std::cout << "Ʈ�� : " << trollCount << std::endl;
		std::cout << "------------------" << std::endl;
		std::cout << std::endl;
	}

	void Log(const std::string& message);	// Log ��� �� ���

	void Init();		// �ʱ�ȭ
	void Progress();	// ���� ����
	bool Update();		// ���� ������ ������Ʈ
	void Destroy();		// ������ ����

private:
	Monster* GenMonster(int playerLevel);

};
