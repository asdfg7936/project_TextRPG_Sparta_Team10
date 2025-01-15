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
#include "Boss.h"
#include "Store.h"

GameManager* GameManager::instance = nullptr;
Store* Store::instance = nullptr;

#pragma region Constructor
void GameManager::Log(const std::string& message)
{
	if (logFile.is_open()) 
	{
		logFile << message << std::endl;
	}
	std::cout << message << std::endl;
}
#pragma endregion


void GameManager::Init()
{
	Store::getInstance();
	// �÷��̾� �̸� �Է�
	std::string playerName = "";
	std::cout << "�÷��̾��� �̸��� �Է��ϼ��� : ";
	std::cin >> playerName;
	Character::getInstance(playerName);
	std::cout << "\n\n\n";

	// �ʹ� ���丮 ���
	FRM->OpenFile(L"../story/intro.txt");
	FRM->PrintLineAll();
	FRM->CloseFile();

	// �ʹ� ���丮 2
	FRM->OpenFile(L"../story/intro2.txt");
	FRM->PrintLineAll(false);
	FRM->CloseFile();

	std::cout << "\n\n\n";

	// �÷��̾� ���� 2�� �����ϰ� ����
	Character::getInstance()->levelUp();

	//�ʹ� ���丮 3
	FRM->OpenFile(L"../story/intro3.txt");
	FRM->PrintLineAll(false);
	FRM->CloseFile();

	std::cout << "\n\n\n";
}

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
	Store* store = Store::getInstance();
	
	//���� ��ȯ
	Monster* genMonster = GenMonster(Character::getInstance()->getLevel());
	
	int Select = 0;
	std::cout << "------------------" << endl;
	std::cout << "1�� : ����" << endl;
	std::cout << "2�� : ���� Ȯ��" << endl;
	std::cout << "3�� : �κ��丮 Ȯ��" << endl;
	std::cout << "4�� : ���� ����" << endl;
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
		store->showList();
		int storeSelect = 0;
		std::cout << "1�� : ������ ����" << std::endl;
		std::cout << "2�� : ������ �Ǹ�" << std::endl;
		std::cout << "3�� : ���� ������" << std::endl;
		std::cout << std::endl;
		std::cout << "���� �ൿ�� �����ϼ��� : ";
		std::cin >> storeSelect;
		std::cout << std::endl;

		// ������ ���� �� ����
		if (storeSelect == 1)
		{
			store->showList();
			std::cout << "�����ϰ��� �ϴ� �������� ��ȣ�� �Է����ּ���";
			int buySelect = 0;
			std::cin >> buySelect;
			store->buyStuff(buySelect);
			std::cout << std::endl;
		}
		else if (storeSelect == 2)
		{
			store->showList();
			player->showInventory();
			std::cout << "�Ǹ��ϰ��� �ϴ� �������� ��ȣ�� �Է����ּ���";
			int sellSelect = 0;
			std::cin >> sellSelect;
			store->sellStuff(sellSelect);
			std::cout << std::endl;
		}
		// ���� �Ϸ� �� ���� Ż��
		else if (storeSelect == 3)
		{
			Select = 3;
		}
		
	}

	if (2 == Select)
	{
		player->displayStatus();
		displayKillCounts();
	}

	if (3 == Select)
	{
		player->showInventory();
	}

	if (4 == Select)
	{
		std::cout << "�߻��� " << genMonster->mGetName() << "��(��) ����߽��ϴ�.\n";

		//���� ���� ���
		genMonster->mDisplayStatus();
		std::cin.get();

		// ����
		while (genMonster->mGetHealth() > 0 && player->IsAlive())
		{
			std::cin.get();  //  enter ġ�� �� �ѱ��

			// �÷��̾� ���� ���
			player->usePotion();
			
			//	�÷��̾ ���� ����
			genMonster->mTakeDamage(player->getAttack());
			std::cout << player->getName() << "��(��) " << genMonster->mGetName() << "��(��) �����߽��ϴ�." << std::endl;
			std::cout << genMonster->mGetName() << "��(��) " << player->getAttack() << "��ŭ ������� �Ծ����ϴ�." << std::endl;
			std::cout << genMonster->mGetName() << "�� ���� ü�� : " << genMonster->mGetHealth() << " / " << genMonster->mGetMaxHealth() << std::endl;

			// ����
			if (genMonster->mGetName() == "��ũ ����")
			{
				float per = static_cast<float>(genMonster->mGetHealth()) / genMonster->mGetMaxHealth() * 100;
				std::cout << "( Boss HP " << per << "% )\n\n";
				static_cast<Boss*>(genMonster)->SoundEffect(per);
			}
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

void GameManager::Destroy()
{
	GameManager::DestroyInstance();
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
/// </summary>
Monster* GameManager::GenMonster(int playerLevel)
{
	Monster* result = nullptr;

	std::vector<Monster*> Monsters;
	Monsters.push_back(new Wolf(playerLevel));
	Monsters.push_back(new Goblin(playerLevel));
	Monsters.push_back(new Orc(playerLevel));
	Monsters.push_back(new Troll(playerLevel));
	Monsters.push_back(new Boss(playerLevel));

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
	else if (playerLevel < 9)
	{
		// ��ũ, Ʈ�� (2,3)
		int idx = rand() % 2 + 2;	// 0 ~ 1
		result = Monsters[idx];
	}
	else if (playerLevel == 10)
	{
		int idx = 4;
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
		FRM->OpenFile(L"../story/Dead.txt");
		FRM->PrintLineAll();
		FRM->CloseFile();
	}

}
#pragma endregion