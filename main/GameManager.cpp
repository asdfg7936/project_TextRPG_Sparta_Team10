#include "GameManager.h"
#include "../Character/Character.h"
#include "FileReaderManager.h"
#include <vector>
#include "Monster.h"
#include "Wolf.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"

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

	// enter �Է� -> ����
	int Select = 0;	// true : ����
	std::cout << "������ ������ 1�� �����ּ���";
	std::cout << "�ɷ�ġ�� ������ 2�� �����ּ���";
	std::cout << "������ �����Ϸ��� 3�� �����ּ���";
	std::cin >> Select;
	

	// ������ �鸮�� �ȴٸ� -> �� ��°� ���� �����ؼ� ���� (�� : ����, ������ ����)
	if(1 == Select)
	{
		// ������ ��� ���
		 
		// ������ ���� �� ����

		// ���� �Ϸ� �� ���� Ż��
	}

	if (2 == Select)
	{
		player->displayStatus();
	}

	if (3 == Select)
	{
		Monster* genMonster = GenMonster(Character::getInstance()->getLevel());
		std::cout << "�߻��� " << genMonster->mGetName() << "��(��) ����߽��ϴ�.\n";
		//���� ���� ���
		//genMonster->displayStatus();
		// ����
		// ������ ü���� 0 �ʰ� �̰� �÷��̾ ������� ��
		while (genMonster->mGetHealth() > 0 && player->IsAlive())
		{
			//std::cin.get();  //  enter ġ�� �� �ѱ��
			// if(ü���� 50% ���ϸ� && ü�� ���� �����ϰ� ������)
			// {
			//	ü�� ������ ����Ѵ�.
			// }
			// else if(������ ������ �����ϰ� ������)
			// {
			//	30% Ȯ���� ���
			// }
			// else
			// {
			//	����
			genMonster->mTakeDamage(player->getAttack());
			std::cout << player->getName << "��(��) " << genMonster->mGetName << "�� �����߽��ϴ�." << std::endl;
			std::cout << genMonster->mGetName << "�� " << player->getAttack << "��ŭ ������� �Ծ����ϴ�." << std::endl;
			// }

			// ���Ͱ� �÷��̾� ����
			player->TakeDamage(genMonster->mGetAttack());
			std::cout << genMonster->mGetName << "��(��) " << player->getName << "�� �����߽��ϴ�." << std::endl;
			std::cout << player->getName << "�� " << genMonster->mGetAttack << "��ŭ ������� �Ծ����ϴ�." << std::endl;
		}
	}
	// ���� ����
	

	// ���Ͱ� ���� ���
	if (genMonster->mGetHealth() <= 0)
	{
		std::cout << genMonster->mGetName << "��(��) �׾����ϴ�." <<  std::endl;
		std::cout << "���� ������ ȹ���߽��ϴ�." << std::endl;
		// ���Ͱ� ������? -> ����ġ/��� ȹ��
		int rndGold = rand() % 11 + 10;
		player->setGold(player->getGold() + rndGold);
		std::cout << rndGold << " ��� ȹ��" << std::endl;
		player->setExperience(player->getExperience() + genMonster->mGetExp());
		std::cout << genMonster->mGetExp() << " ����ġ ȹ��" << std::endl;
	}

	//������ üũ
	if (player->getExperience >= player->getExperienceToNextLevel)
	{
		player->levelUp;
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

	if (playerLevel < 5)
	{
		// ����, ��� (0, 1)
		int idx = rand() % 2;	// 0 ~ 1
		result = Monsters[idx];
	}
	else if (playerLevel < 9)
	{
		// (����, ���) + ����, ��ũ (0,1,2)
		int idx = rand() % 3;	// 0 ~ 2
		result = Monsters[idx];
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
	while (bPlayerAlive || Character::getInstance()->getLevel() < 10)
	{
		bPlayerAlive = Update();
	}

	// �������� ���� ����

}
#pragma endregion