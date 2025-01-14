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
/// 寃 � 珥湲고 댁쇳 寃 異媛
/// ex) �댁 罹由� , ...
/// </summary>
void GameManager::Init()
{
	// �댁 대 �
	std::string playerName = "";
	std::cout << "�댁댁 대 �ν몄 : ";
	std::cin >> playerName;
	Character::getInstance(playerName);
	std::cout << playerName;	// debug

	// 珥諛 ㅽ由 異�
	FileReaderManager* FRM = FileReaderManager::GetInstance();
	FRM->OpenFile("../test.txt");
	FRM->CloseFile();

	// �댁 �踰 2濡 ㅼ怨 
	Character::getInstance()->levelUp();
}

/// <summary>
/// 寃 濡吏
/// 
///  대 諛댁쇳 紐⑤ 寃
///	ex)
///		�댁 � (怨듦꺽? ㅽ? 댄? �?)
///		�댁댁 �κ 곕Ⅸ 몄
///			case1 : �댁닿 紐ъㅽ곕� 怨듦꺽.
///			case2 : �댁닿 ㅽъ대 -> MP 遺議깊
///			case3 : 댄 ъ⑺ -> 洹몄곕Ⅸ ④낵
///			case4 : � NPC 留щ -> 댄 ъ쇳  遺議깊. 援щℓ.
///		�댁 or 紐ъㅽ곌 二쎌
///			case1 : �댁 二쎌 -> 寃  (濡洹몃쇱댄)
///			case2 : 紐ъㅽ곌 二쎌 -> 寃쏀移, 댄  -> �踰⑥ or λ瑜 媛怨 or 대깽몃
///		紐⑹吏 or ㅼ 吏   
/// 
/// </summary>

/// <summary>
/// 
/// 紐ъㅽ : , 怨釉由, ㅽ, 몃·
///	 
/// �댁 �踰 1 ~ 4  : , 怨釉由
/// �댁 �踰 5 ~ 8 : (, 怨釉由) + 媛, ㅽ
/// �댁 �踰 9 ~ 10 : ㅽ, 몃·
/// 
/// </summary>
bool GameManager::Update()
{
	Character* player = Character::getInstance();

	//紐ъㅽ 
	Monster* genMonster = GenMonster(Character::getInstance()->getLevel());

	// enter � -> 
	int Select = 0;	// true : �
	std::cout << "臾댁 寃듬源?" << std::endl;
	std::cout << "1踰 : �" << std::endl;
	std::cout << "2踰 : λμ " << std::endl;
	std::cout << "3踰 : � " << std::endl;
	std::cin >> Select;

	// � ㅻ━寃 ㅻ㈃ ->  щ嫄 닿 댁 援щℓ ( : 臾쇱,  臾쇱)
	if(1 == Select)
	{
		// 댄 紐⑸ 異�
		 
		// 댄  諛 援щℓ

		// 援щℓ 猷  � 異
	}

	if (2 == Select)
	{
		player->displayStatus();
	}

	if (3 == Select)
	{
		
		std::cout << "쇱 " << genMonster->mGetName() << "(媛) 異紐고듬.\n";
		//紐ъㅽ ㅽ 異�
		//genMonster->displayStatus();
		// �
		// 紐ъㅽ곗 泥대μ 0 珥怨 닿� �댁닿 댁 
		while (genMonster->mGetHealth() > 0 && player->IsAlive())
		{
			//std::cin.get();  //  enter 移硫  湲곌린
			// if(泥대μ 50% 댄硫 && 泥대 臾쇱 吏怨 쇰㈃)
			// {
			//	泥대 臾쇱쎌 ъ⑺.
			// }
			// else if( 臾쇱쎌 吏怨 쇰㈃)
			// {
			//	30% 瑜濡 ъ
			// }
			// else
			// {
			//	怨듦꺽
			genMonster->mTakeDamage(player->getAttack());
			std::cout << player->getName() << "이(가) " << genMonster->mGetName() << "을 공격했습니다." << std::endl;
			std::cout << genMonster->mGetName() << "은 " << player->getAttack() << "만큼 대미지를 입었습니다." << std::endl;
			// }

			// 紐ъㅽ곌 �댁 怨듦꺽
			player->TakeDamage(genMonster->mGetAttack());
			std::cout << genMonster->mGetName() << "이(가) " << player->getName() << "을 공격했습니다." << std::endl;
			std::cout << player->getName() << "은 " << genMonster->mGetAttack() << "만큼 대미지를 입었습니다." << std::endl;
		}
	}

	// 몬스터가 죽은 경우
	if (GenMonster->mGetHealth() <= 0)
	{
		std::cout << GenMonster->mGetName() << "이(가) 죽었습니다." << std::endl;
		std::cout << "다음 보상을 획득했습니다." << std::endl;
		// 몬스터가 죽으면? -> 경험치/골드 획득
		int rndGold = rand() % 11 + 10;
		player->setGold(player->getGold() + rndGold);
		std::cout << rndGold << " 골드 획득" << std::endl;
		player->setExperience(player->getExperience() + GenMonster->mGetExp());
		std::cout << GenMonster->mGetExp() << " 경험치 획득" << std::endl;
	}

	//�踰⑥ 泥댄
	if (player->getExperience() >= player->getExperienceToNextLevel() && player->getLevel() < 10)
	{
		player->levelUp();
	}


	return player->IsAlive();
}

/// <summary>
/// 
/// container = [ , 怨釉由, ㅽ, 몃· ]
///                0      1      2     3
/// 
/// �댁 �踰 1 ~ 4  : , 怨釉由
/// �댁 �踰 5 ~ 8 : (, 怨釉由) + 媛, ㅽ
/// �댁 �踰 9 ~ 10 : ㅽ, 몃·
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
		// , 怨釉由 (0, 1)
		int idx = rand() % 2;	// 0 ~ 1
		result = Monsters[idx];
	}
	else if (playerLevel < 8)
	{
		// (, 怨釉由) + 媛, ㅽ (0,1,2)
		int idx = rand() % 3;	// 0 ~ 2
		result = Monsters[idx];
	}
	else
	{
		// ㅽ, 몃· (2,3)
		int idx = rand() % 2 + 2;	// 0 ~ 1
		result = Monsters[idx];
	}

	return result;
}

#pragma region Progress
// 寃 濡吏 �ㅼ＜ 怨
void GameManager::Progress()
{
	// 寃 醫猷 議곌굔 : Player щ  �댁댁 �踰⑥ 10 誘몃쇰
	bool bPlayerAlive = true;
	while (bPlayerAlive || Character::getInstance()->getLevel() < 10)
	{
		bPlayerAlive = Update();
	}

	// 寃醫猷 濡吏 

}
#pragma endregion