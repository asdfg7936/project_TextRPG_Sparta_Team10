#include "FileReaderManager.h"

FileReaderManager* FileReaderManager::instance = nullptr;

void FileReaderManager::ReadFile()
{
	std::string line;
	bool bEnd = false;
	while (false == bEnd)
	{
		if (std::getline(instance->readFile, line))
		{
			lineContainer.push_back(line);
			
			if (readFile.eof())
			{
				bEnd = true;
				std::cout << "Reached the end of the file." << std::endl;
			}

			if (readFile.fail()) {
				std::cerr << "An error occurred while reading the file!" << std::endl;
			}
			else if (readFile.good()) {
				std::cout << "The file stream is in good condition." << std::endl;
			}
		}
	}

	int a = 0;
}

bool FileReaderManager::OpenFile(std::string filePath)
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

void FileReaderManager::CloseFile()
{
	readFile.close();
}
