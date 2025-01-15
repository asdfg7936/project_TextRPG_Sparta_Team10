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

		logFile.open("../log.txt", std::ios::app); // 로그 파일 열기 (append 모드)
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
		std::cout << "현재까지 잡은 몬스터 수" << std::endl;
		std::cout << "늑대 : " << wolfCount << std::endl;
		std::cout << "고블린 : " << goblinCount << std::endl;
		std::cout << "오크 : " << orcCount << std::endl;
		std::cout << "트롤 : " << trollCount << std::endl;
		std::cout << "------------------" << std::endl;
		std::cout << std::endl;
	}

	void Log(const std::string& message);	// Log 출력 및 기록

	void Init();		// 초기화
	void Progress();	// 게임 로직
	bool Update();		// 게임 데이터 업데이트
	void Destroy();		// 마무리 정리

private:
	Monster* GenMonster(int playerLevel);

};
