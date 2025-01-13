#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileReaderManager
{
private:
	static FileReaderManager* instance;

	std::ifstream readFile;	// Input File Stream
	std::vector<std::string> lineContainer;

	FileReaderManager()
	{
		std::cout << "[ Set File Reader Manager ]" << std::endl;
	}

	~FileReaderManager()
	{
	}

	FileReaderManager(const FileReaderManager&) = delete;
	FileReaderManager& operator=(const FileReaderManager&) = delete;

public:
	static FileReaderManager* GetInstance()
	{
		if (nullptr == instance)
		{
			instance = new FileReaderManager();
		}
		return instance;
	}

	static void DestroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
			std::cout << "[ Delete File Reader Manager ]" << std::endl;
		}
	}

private:
	void ReadFile();

public:
	bool OpenFile(std::string filePath);
	void CloseFile();

};
