#pragma once
#include <iostream>
#include <fstream>

class Monster;

class GameManager
{
private:
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

	void Log(const std::string& message);	// Log 출력 및 기록
	void Init();							// 초기화
	void Progress();						// 게임 로직 총 집합
	bool Update();

private:
	Monster* GenMonster(int playerLevel);

};
