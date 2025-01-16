#include "FileReaderManager.h"

#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::milliseconds

#include <windows.h>

FileReaderManager* FileReaderManager::instance = nullptr;

/// <summary>
/// 
/// std::getline�� �⺻������ std::string�� �Բ� ���ȴ�.
/// std::string�� UTF-8 ���ڿ��� �ٷ� �� ���� ������ �ǹ̸� �ùٸ��� ó������ ���Ѵ�.
/// 
/// std::wifstream
/// std::wstring
/// 
/// </summary>
void FileReaderManager::ReadFile()
{
	std::wstring line;
	bool bEnd = false;
	while (false == bEnd)
	{
		if (std::getline(instance->readFile, line))
		{
			lineContainer.push_back(line);
			
			if (readFile.eof())
				bEnd = true;

			if (readFile.fail()) 
			{
				std::cerr << "An error occurred while reading the file!" << std::endl;
				bEnd = true;
			}
		}
	}
}

bool FileReaderManager::OpenFile(std::wstring filePath)
{
	readFile.open(filePath);
	if (false == readFile.is_open())
	{
		std::cout << "Failed to open file for reading!" << std::endl;
		return false;
	}
	ReadFile();
	return true;
}

void FileReaderManager::PrintLine(int idx, std::wstring playerName, bool bTypeEffect)
{
	if (playerName != L"")
	{
		insertPlayerName(playerName);
	}

	if (bTypeEffect)
	{
		typingEffect(lineContainer[idx]);
	}
	else
	{
		std::wcout << lineContainer[idx];
	}

}

void FileReaderManager::PrintLineAll(std::wstring playerName, bool bTypeEffect)
{
	if (playerName != L"")
	{
		insertPlayerName(playerName);
	}

	for (int i = 0; i < lineContainer.size(); ++i)
	{
		if (bTypeEffect)
		{
			typingEffect(lineContainer[i]);
		}
		else
		{
			std::wcout << lineContainer[i];
		}
		std::cout << std::endl;
	}
}

void FileReaderManager::CloseFile()
{
	lineContainer.clear();
	readFile.close();
}

void FileReaderManager::typingEffect(const std::wstring& text, int delay)
{
	for (wchar_t ch : text) {
		std::wcout << ch << std::flush; // flush�� ����Ͽ� �ﰢ ���
		std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // ������
	}
}

void FileReaderManager::insertPlayerName(std::wstring playerName)
{
	for (int i = 0; i < lineContainer.size(); i++)
	{
		wchar_t target = L'#';
		size_t pos = lineContainer[i].find(target);

		while (pos != std::string::npos) {
			if (pos != std::string::npos)
			{
				lineContainer[i].replace(pos, 1, playerName);
			}
			pos = lineContainer[i].find(target, pos + 1);
		}
	}
}