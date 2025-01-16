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
#include "Enum.h"

GameManager* GameManager::instance = nullptr;
Store* Store::instance = nullptr;

#pragma region Game Logic

void GameManager::Init()
{
	SetPlayerCharacter();	// �ʱ� �÷��̾� �̸� ���� �� ����

	std::cout << "\n\n\n";

	Intro();	// �ʹ� ���丮 ��� �� �÷��̾� �⺻ ����
}

void GameManager::Progress()
{
	// ���� ���� ���� : 
	//		1. ĳ���� ���
	//		2. ���� óġ ����
	bool bPlayerAlive = true;
	// �÷��̾ ����ְ�, ������ ���� �ʾ����� ���� ����
	// �� �� �ϳ��� ������ ���� ��
	while (bPlayerAlive && false == bBossDeath)
	{
		bPlayerAlive = Update();
	}

	// �������� ���� ����
	if (false == bPlayerAlive)
	{
		std::cout << std::endl;
		FRM->OpenFile(L"../story/Dead.txt");
		FRM->PrintLineAll(Character::getInstance()->getName());
		FRM->CloseFile();
	}
}

bool GameManager::Update()
{
	Character* player = Character::getInstance();
	Store* store = Store::getInstance();
	Monster* genMonster = nullptr;

	// �÷��̾� �Է�
	int Select = SelectOption();
	switch (Select)
	{
	case 1:	// ����
		SelectStore();
		break;
	case 2:	// ���� Ȯ��
		SelectStatus();
		break;
	case 3:	// �κ��丮 Ȯ��
		SelectInventory();
		break;
	case 4:	// ����
		BattleReward(SelectBattle());
		break;
	case 9:	// ���� ����
		return SelectEndGame();
	default:
		__noop;
	}

	return player->IsAlive();
}

void GameManager::Destroy()
{
	GameManager::DestroyInstance();
}

#pragma endregion


#pragma region Player Input

int GameManager::SelectOption()
{
	int Select = 0;
	std::cout << "\n\n����������������������\n\n";
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

	return Select;
}

void GameManager::SelectStore()
{
	Store* store = Store::getInstance();
	Character* player = Character::getInstance();

	// ������ �鸮�� �ȴٸ� -> �� ��°� ���� �����ؼ� ���� (�� : ����, ������ ����)
	// ������ ��� ���
	GameManager::setConsoleColor(EColor::GREEN);
	store->showList();
	GameManager::setConsoleColor(EColor::WHITE);
	int storeSelect = 0;
	std::cout << "1�� : ������ ����" << std::endl;
	std::cout << "\n2�� : ������ �Ǹ�" << std::endl;
	std::cout << "\n[ �ٸ� ���� �Է��ϸ� ������ �����ϴ�. ]\n\n";
	std::cout << "���� �ൿ�� �����ϼ��� : ";
	std::cin >> storeSelect;
	std::cout << std::endl;

	// ������ ���� �� ����
	if (storeSelect == 1)
	{
		std::cout << "�����ϰ��� �ϴ� �������� ��ȣ�� �Է����ּ��� : ";
		int buySelect = 0;
		std::cin >> buySelect;
		store->buyStuff(buySelect);
		std::cout << std::endl;
	}
	else if (storeSelect == 2)
	{
		GameManager::setConsoleColor(EColor::GREEN);
		player->showInventory();
		GameManager::setConsoleColor(EColor::WHITE);
		std::cout << "�Ǹ��ϰ��� �ϴ� �������� ��ȣ�� �Է����ּ��� : ";
		int sellSelect = 0;
		std::cin >> sellSelect;
		store->sellStuff(sellSelect);
		std::cout << std::endl;
	}
}

void GameManager::SelectStatus()
{
	Character* player = Character::getInstance();

	player->displayStatus();
	displayKillCounts();
}

void GameManager::SelectInventory()
{
	Character* player = Character::getInstance();

	GameManager::setConsoleColor(EColor::GREEN);
	player->showInventory();
	GameManager::setConsoleColor(EColor::WHITE);
}

Monster* GameManager::SelectBattle()
{
	Character* player = Character::getInstance();

	// ���� ���� 
	Monster* genMonster = GenMonster(Character::getInstance()->getLevel());
	GameManager::setConsoleColor(EColor::RED);
	std::cout << "\n�߻��� " << genMonster->mGetName() << "��(��) ����߽��ϴ�.\n";
	GameManager::setConsoleColor(EColor::WHITE);

	if (genMonster->mGetName() == "��ũ ����")
	{
		static_cast<Boss*>(genMonster)->SoundEffect(EBossCondition::INTRO);
	}

	// ���� ���� ���
	genMonster->mDisplayStatus();
	std::cin.get();

	// ����
	while (genMonster->mGetHealth() > 0 && player->IsAlive())
	{
		// enter ġ�� �� �ѱ��
		std::cin.get();

		// �÷��̾� ���� ���
		GameManager::setConsoleColor(EColor::AQUA);
		player->usePotion();
		GameManager::setConsoleColor(EColor::WHITE);

		//	�÷��̾ ���� ����
		genMonster->mTakeDamage(player->getAttack());
		std::wcout << player->getName() << L"��(��) ";
		std:cout << genMonster->mGetName() << "��(��) �����߽��ϴ�." << std::endl;
		std::cout << genMonster->mGetName() << "��(��) " << player->getAttack() << "��ŭ ������� �Ծ����ϴ�." << std::endl;
		std::cout << genMonster->mGetName() << "�� ���� ü�� : " << genMonster->mGetHealth() << " / " << genMonster->mGetMaxHealth() << std::endl;
		std::cin.get();

		if (genMonster->mGetName() == "��ũ ����"
			&& genMonster->mGetHealth() == 0)
		{
			static_cast<Boss*>(genMonster)->SoundEffect(EBossCondition::DEATH);
			return genMonster;
		}

		// ���Ͱ� �÷��̾� ����
		if (genMonster->mGetHealth() > 0)
		{
			player->TakeDamage(genMonster->mGetAttack());
			std::cout << genMonster->mGetName() << "��(��) ";
			std::wcout << player->getName() << L"��(��) �����߽��ϴ�." << std::endl;
			std::wcout << player->getName() << L"��(��) ";
			std::cout << genMonster->mGetAttack() << "��ŭ ������� �Ծ����ϴ�." << std::endl;
			std::cout << "���� ü�� : " << player->getHealth() << " / " << player->getMaxhealth() << std::endl;
		}

		if (genMonster->mGetName() == "��ũ ����")
		{
			Boss* boss = static_cast<Boss*>(genMonster);
			float per = static_cast<float>(genMonster->mGetHealth()) / genMonster->mGetMaxHealth() * 100;

			if (boss->GetHalfAlarm() && per <= 50)
			{
				static_cast<Boss*>(genMonster)->SoundEffect(EBossCondition::HALF);
			}
			else if (boss->GetAlmostAlarm() && per <= 20)
			{
				static_cast<Boss*>(genMonster)->SoundEffect(EBossCondition::ALMOST);
			}
		}
	}

	return genMonster;
}

void GameManager::BattleReward(Monster* genMonster)
{
	Character* player = Character::getInstance();

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
		else if (genMonster->mGetName() == "��ũ ����")
		{
			GM->SetGameEndCondition(true);
			return;
		}

		std::cout << genMonster->mGetName() << "��(��) �׾����ϴ�." << std::endl;
		std::cin.get();

		std::cout << "���� ������ ȹ���߽��ϴ�." << std::endl;
		GameManager::setConsoleColor(EColor::GREEN);
		int rndGold = rand() % 11 + 10;
		player->setGold(player->getGold() + rndGold);
		std::cout << rndGold << " ��� ȹ��" << std::endl;
		if (player->getLevel() < 10)
		{
			player->setExperience(player->getExperience() + genMonster->mGetExp());
			std::cout << genMonster->mGetExp() << " ����ġ ȹ��" << std::endl;
		}
		GameManager::setConsoleColor(EColor::WHITE);
		std::cin.get();
	}

	//������ üũ
	if (player->getExperience() >= player->getExperienceToNextLevel()
		&& player->getLevel() < 10)
	{
		GameManager::setConsoleColor(EColor::YELLOW);
		player->levelUp();
		GameManager::setConsoleColor(EColor::WHITE);
	}
}

bool GameManager::SelectEndGame()
{
	Character* player = Character::getInstance();

	player->setHealth(0);
	std::cout << "������ �����մϴ�." << endl;
	return false;
}

#pragma endregion


#pragma region Function

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
	else if (playerLevel < 10)
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

void GameManager::displayKillCounts() const
{
	{
		std::cout << "\n------------------" << std::endl;
		std::cout << "[ óġ�� ���� ]" << std::endl;
		std::cout << "���� : " << wolfCount << std::endl;
		std::cout << "��� : " << goblinCount << std::endl;
		std::cout << "��ũ : " << orcCount << std::endl;
		std::cout << "Ʈ�� : " << trollCount << std::endl;
		std::cout << "------------------\n" << std::endl;
	}
}

void GameManager::SetPlayerCharacter()
{
	std::wstring playerName = L"";
	std::cout << "�÷��̾��� �̸��� �Է��ϼ��� : ";
	std::wcin >> playerName;
	//std::wcout << playerName;
	Character::getInstance(playerName);
}

void GameManager::Intro()
{
	// �ʹ� ���丮 ���
	FRM->OpenFile(L"../story/intro.txt");
	FRM->PrintLineAll(Character::getInstance()->getName());
	FRM->CloseFile();
	std::cin.get();

	// �ʹ� ���丮 2
	FRM->OpenFile(L"../story/intro2.txt");
	FRM->PrintLineAll(Character::getInstance()->getName());
	FRM->CloseFile();
	std::cin.get();

	// �÷��̾� ���� 2�� �����ϰ� ����
	GameManager::setConsoleColor(EColor::YELLOW);
	Character::getInstance()->levelUp();
	GameManager::setConsoleColor(EColor::WHITE);
	std::cin.get();

	//�ʹ� ���丮 3
	FRM->OpenFile(L"../story/intro3.txt");
	FRM->PrintLineAll(Character::getInstance()->getName());
	FRM->CloseFile();
	std::cin.get();
}

#pragma endregion