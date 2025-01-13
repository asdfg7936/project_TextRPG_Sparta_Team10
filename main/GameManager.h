#pragma once
#include <iostream>

class GameManager
{
private:
	static GameManager* instance;

	GameManager()
	{
		std::cout << "[ Create GameManager ]" << std::endl;
	}

	~GameManager() 
	{
		DestroyInstance();
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
			std::cout << "[ Delete GameManager ]" << std::endl;
		}
	}

};

GameManager* GameManager::instance = nullptr;
