#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

class FileReaderManager
{
private:
	static FileReaderManager* instance;

	//std::ifstream readFile;	// Input File Stream
	//std::vector<std::string> lineContainer;

	std::wifstream readFile;
	std::vector<std::wstring>lineContainer;


	FileReaderManager() 
	{
		readFile.imbue(std::locale(readFile.getloc(), new std::codecvt_utf8<wchar_t>));
		std::wcout.imbue(std::locale(""));
	}
	~FileReaderManager() {}

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
	bool OpenFile(std::wstring filePath);
	void PrintLine(int idx);	// lineContainer �� ����ִ� ������ ����Ѵ�.
	void PrintLineAll();		// lineContainer �� ����ִ� ������ ���� ����Ѵ�.
	void CloseFile();

};
