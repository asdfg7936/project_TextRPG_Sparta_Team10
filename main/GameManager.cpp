#include "GameManager.h"
#include "../Character/Character.h"
#include "FileReaderManager.h"
#include <vector>
#include "Monster.h"
#include "Wolf.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "StrongMonster.h"

GameManager* GameManager::instance = nullptr;

#pragma region Constructor
void GameManager::Log(const std::string& message)
{
	if (logFile.is_open()) {
		logFile << message << std::endl;
	}
	std::cout << message << std::endl;
}
#pragma endregion

/// <summary>
/// ���� ������ �ʱ�ȭ �ؾ��ϴ� �͵� �߰�
/// ex) �÷��̾� ĳ���� ����, ��...
/// </summary>
void GameManager::Init()
{
	// �÷��̾� �̸� �Է�
	std::string playerName = "";
	std::cout << "�÷��̾��� �̸��� �Է��ϼ��� : ";
	std::cin >> playerName;
	Character::getInstance(playerName);
	std::cout << playerName;	// debug

	// �ʹ� ���丮 ���
	FileReaderManager* FRM = FileReaderManager::GetInstance();
	FRM->OpenFile("../test.txt");
	FRM->CloseFile();

	// �÷��̾� ���� 2�� �����ϰ� ����
	Character::getInstance()->levelUp();
}

/// <summary>
/// ���� ����
/// 
/// �� �ϵ��� �߻��ؾ��ϴ� ��� ��
///	ex)
///		�÷��̾� �Է� (����? ��ų? ������? ����?)
///		�÷��̾��� �Է°��� ���� ��ȣ�ۿ�
///			case1 : �÷��̾ ���͸� �����ߴ�.
///			case2 : �÷��̾ ��ų������ -> MP �����ϴ�
///			case3 : �������� ����ߴ� -> �׿����� ȿ��
///			case4 : ���� NPC ������ -> ������ ����ϴµ� ���� �����ϴ�. �����ߴ�.
///		�÷��̾� or ���Ͱ� ����
///			case1 : �÷��̾� ���� -> ���� �� (�α׶���ũ)
///			case2 : ���Ͱ� �׾��� -> ����ġ, ������ ��� -> ������ or ��� ���Ƴ������ְ� or �̺�Ʈ�߻�
///		������ or ���� ������ ���� ���� 
/// 
/// </summary>

/// <summary>
/// 
/// ���� : ����, ���, ��ũ, Ʈ��
///	 
/// �÷��̾� ���� 1 ~ 4  : ����, ���
/// �÷��̾� ���� 5 ~ 8 : (����, ���) + ����, ��ũ
/// �÷��̾� ���� 9 ~ 10 : ��ũ, Ʈ��
/// 
/// </summary>
bool GameManager::Update()
{
	Character* player = Character::getInstance();
	
	//���� ��ȯ
	Monster* genMonster = GenMonster(Character::getInstance()->getLevel());
	
	int Select = 0;
	std::cout << "------------------" << endl;
	std::cout << "1�� : ����" << endl;
	std::cout << "2�� : ���� Ȯ��" << endl;
	std::cout << "3�� : ���� ����" << endl;
	std::cout << "9�� : ���� ����" << endl;
	std::cout << "------------------" << endl;
	std::cout << std::endl;
	std::cout << "���� �ൿ�� �����ϼ��� : ";
	std::cin >> Select;
	std::cout << endl;
	
	
	// ������ �鸮�� �ȴٸ� -> �� ��°� ���� �����ؼ� ���� (�� : ����, ������ ����)
	if (1 == Select)
	{
		// ������ ��� ���

		// ������ ���� �� ����

		// ���� �Ϸ� �� ���� Ż��
	}

	if (2 == Select)
	{
		player->displayStatus();
		displayKillCounts();
	}

	if (3 == Select)
	{
		std::cout << "�߻��� " << genMonster->mGetName() << "��(��) ����߽��ϴ�.\n";
		//���� ���� ���
		genMonster->mDisplayStatus();
		std::cin.get();
		// ����
		// ������ ü���� 0 �ʰ� �̰� �÷��̾ ������� ��
		while (genMonster->mGetHealth() > 0 && player->IsAlive())
		{
			std::cin.get();  //  enter ġ�� �� �ѱ��

			// �÷��̾� ���� ���
			//player->usePotion();
			
			//	�÷��̾ ���� ����
			genMonster->mTakeDamage(player->getAttack());
			std::cout << player->getName() << "��(��) " << genMonster->mGetName() << "��(��) �����߽��ϴ�." << std::endl;
			std::cout << genMonster->mGetName() << "��(��) " << player->getAttack() << "��ŭ ������� �Ծ����ϴ�." << std::endl;
			std::cout << genMonster->mGetName() << "�� ���� ü�� : " << genMonster->mGetHealth() << " / " << genMonster->mGetMaxHealth() << std::endl;
			std::cin.get();

			// ���Ͱ� �÷��̾� ����
			if (genMonster->mGetHealth() > 0)
			{
				player->TakeDamage(genMonster->mGetAttack());
				std::cout << genMonster->mGetName() << "��(��) " << player->getName() << "��(��) �����߽��ϴ�." << std::endl;
				std::cout << player->getName() << "��(��) " << genMonster->mGetAttack() << "��ŭ ������� �Ծ����ϴ�." << std::endl;
				std::cout << "���� ü�� : " << player->getHealth() << " / " << player->getMaxhealth() << std::endl;
			}
		}
	}
	if (9 == Select)
	{
		player->setHealth(0);
		std::cout << "������ �����մϴ�." << endl;
		return false;
	}

	// ���Ͱ� ���� ���
	if (genMonster->mGetHealth() <= 0)
	{
		if (genMonster->mGetName() == "����") 
		{
			wolfCount++;
		}
		else if (genMonster->mGetName() == "���")
		{
			goblinCount++;
		}
		else if (genMonster->mGetName() == "��ũ")
		{
			orcCount++;
		}
		else if (genMonster->mGetName() == "Ʈ��")
		{
			trollCount++;
		}
		std::cout << genMonster->mGetName() << "��(��) �׾����ϴ�." << std::endl;
		std::cin.get();
		std::cout << "���� ������ ȹ���߽��ϴ�." << std::endl;
		// ���Ͱ� ������? -> ����ġ/��� ȹ��
		int rndGold = rand() % 11 + 10;
		player->setGold(player->getGold() + rndGold);
		std::cout << rndGold << " ��� ȹ��" << std::endl;
		if (player->getLevel() < 10)
		{
			player->setExperience(player->getExperience() + genMonster->mGetExp());
			std::cout << genMonster->mGetExp() << " ����ġ ȹ��" << std::endl;
		}
		std::cin.get();
	}

	//������ üũ
	if (player->getExperience() >= player->getExperienceToNextLevel() && player->getLevel() < 10) {
		player->levelUp();
	}
	if (player->getLevel() == 10)
	{
		player->setExperience(0);
	}

	return player->IsAlive();
}

/// <summary>
/// 
/// container = [ ����, ���, ��ũ, Ʈ�� ]
///                0      1      2     3
/// 
/// �÷��̾� ���� 1 ~ 4  : ����, ���
/// �÷��̾� ���� 5 ~ 8 : (����, ���) + ����, ��ũ
/// �÷��̾� ���� 9 ~ 10 : ��ũ, Ʈ��
/// 
/// 
/// </summary>
Monster* GameManager::GenMonster(int playerLevel)
{
	Monster* result = nullptr;

	std::vector<Monster*> Monsters;
	Monsters.push_back(new Wolf(playerLevel));
	Monsters.push_back(new Goblin(playerLevel));
	Monsters.push_back(new Orc(playerLevel));
	Monsters.push_back(new Troll(playerLevel));

	if (playerLevel < 4)
	{
		// ����, ��� (0, 1)
		int idx = rand() % 2; // 0 ~ 1
		result = Monsters[idx];	
	}
	else if (playerLevel < 7)
	{
		// (����, ���) + ����, ��ũ (0,1,2)
		int idx = rand() % 3;	// 0 ~ 2
		result = Monsters[idx];

		if (idx < 2) {
			result = new StrongMonster(result);
		}
	}
	else
	{
		// ��ũ, Ʈ�� (2,3)
		int idx = rand() % 2 + 2;	// 0 ~ 1
		result = Monsters[idx];
	}

	return result;
}

#pragma region Progress
// ���� ���� �����ִ� ��
void GameManager::Progress()
{
	// ���� ���� ���� : Player ��� �Ǵ� �÷��̾��� ������ 10 �̸��϶�
	bool bPlayerAlive = true;
	while (bPlayerAlive)
	{
		bPlayerAlive = Update();
	}
	// �������� ���� ����
	if (!bPlayerAlive)
	{
		std::cout << "�÷��̾ ����߽��ϴ�." << std::endl;
	}

}
#pragma endregion