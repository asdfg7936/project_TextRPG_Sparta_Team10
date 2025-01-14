#include "GameManager.h"
#include "../Character/Character.h"
#include "FileReaderManager.h"
#include <vector>
#include "Monster.h"
#include "Wolf.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"


/// <summary>
/// �ѱ� �׽�Ʈ
/// </summary>
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
/// 寃�? ��??�湲고�??�쇳 寃�? ?�媛?
/// ex) ��??��? 罹由��? , ...
/// </summary>
void GameManager::Init()
{
	// ��??��? ?� �?
	std::string playerName = "";
	std::cout << "��??�댁 ?� �ν�?몄�?: ";
	std::cin >> playerName;
	Character::getInstance(playerName);
	std::cout << playerName;	// debug

	// ?�諛 ?��??? ?��
	FileReaderManager* FRM = FileReaderManager::GetInstance();
	FRM->OpenFile("../test.txt");
	FRM->CloseFile();

	// ��??��? �踰 2濡�????? 
	Character::getInstance()->levelUp();
}

/// <summary>
/// 寃�? 濡吏
/// 
///  ?� 諛�??�쇳 紐⑤ 寃�?///	ex)
///		��??��? �? (?�듦�? ?��?? ?��? ��?)
///		��??�댁 ��? 곕Ⅸ 몄�?
///			case1 : ��??�닿? 紐ъㅽ곕� ?�듦�?.
///			case2 : ��??�닿? ?�ъ�??� -> MP ?�議깊
///			case3 : ?��? ??��? -> 洹몄곕Ⅸ ?�낵
///			case4 : ��?NPC 留�?? -> ?��???��?  ?�議깊. ?�щℓ.
///		��??��? or 紐ъㅽ�?? 二쎌
///			case1 : ��??��? 二쎌 -> 寃�?  (濡洹몃쇱?��?)
///			case2 : 紐ъㅽ�?? 二쎌 -> 寃�?移�? ?��? -> �踰?��?or λ?? 媛�??? or ?��?�?
///		紐⑹吏 or ?��?吏�?   
/// 
/// </summary>

/// <summary>
/// 
/// 紐ъㅽ : ?, ???�由, ?��?, 몃�?///	 
/// ��??��? �踰 1 ~ 4  : ?, ???�由
/// ��??��? �踰 5 ~ 8 : (?, ???�由) + 媛�?, ?��?
/// ��??��? �踰 9 ~ 10 : ?��?, 몃�?/// 
/// </summary>
bool GameManager::Update()
{
	Character* player = Character::getInstance();

	//紐ъㅽ 
	Monster* genMonster = GenMonster(Character::getInstance()->getLevel());

	// enter �? -> 
	int Select = 0;	// true : ��?	std::cout << "?�댁 �???�源?" << std::endl;
	std::cout << "1踰�?: ��? << std::endl;
	std::cout << "2踰�?: λμ " << std::endl;
	std::cout << "3踰�?: ��? " << std::endl;
	std::cin >> Select;

	// ��? ?�━寃�??�㈃ ->  ?�? ??? ?��??�щℓ ( : ?�쇱,  ?�쇱)
	if(1 == Select)
	{
		// ?��?紐⑸ ?��
		 
		// ?��? �? ?�щℓ

		// ?�щℓ ?��? ��??��?	}

	if (2 == Select)
	{
		player->displayStatus();
	}

	if (3 == Select)
	{
		
		std::cout << "?��? " << genMonster->mGetName() << "(媛) ?�紐고�???��?.\n";
		//紐ъㅽ ?��??��
		//genMonster->displayStatus();
		// ��?
		// 紐ъㅽ곗�?泥�?μ 0 ?��? ?�� ��??�닿? ?��? 
		while (genMonster->mGetHealth() > 0 && player->IsAlive())
		{
			//std::cin.get();  //  enter 移硫  湲곌�?			// if(泥�?μ 50% ?�硫 && 泥�? ?�쇱 吏?? ?�㈃)
			// {
			//	泥�? ?�쇱?��???��?.
			// }
			// else if( ?�쇱?��?吏?? ?�㈃)
			// {
			//	30% ??濡�??
			// }
			// else
			// {
			//	?�듦�?			genMonster->mTakeDamage(player->getAttack());
			std::cout << player->getName() << "??가) " << genMonster->mGetName() << "??공격?�습?�다." << std::endl;
			std::cout << genMonster->mGetName() << "?� " << player->getAttack() << "만큼 ?�미�?�??�었?�니??" << std::endl;
			// }

			// 紐ъㅽ�?? ��??��? ?�듦�?			player->TakeDamage(genMonster->mGetAttack());
			std::cout << genMonster->mGetName() << "??가) " << player->getName() << "??공격?�습?�다." << std::endl;
			std::cout << player->getName() << "?� " << genMonster->mGetAttack() << "만큼 ?�미�?�??�었?�니??" << std::endl;
		}
	}

	// 몬스?��? 죽�? 경우
	if (GenMonster->mGetHealth() <= 0)
	{
		std::cout << GenMonster->mGetName() << "??가) 죽었?�니??" << std::endl;
		std::cout << "?�음 보상???�득?�습?�다." << std::endl;
		// 몬스?��? 죽으�? -> 경험�?골드 ?�득
		int rndGold = rand() % 11 + 10;
		player->setGold(player->getGold() + rndGold);
		std::cout << rndGold << " 골드 ?�득" << std::endl;
		player->setExperience(player->getExperience() + GenMonster->mGetExp());
		std::cout << GenMonster->mGetExp() << " 경험�??�득" << std::endl;
	}

	//�踰?��?泥댄
	if (player->getExperience() >= player->getExperienceToNextLevel() && player->getLevel() < 10)
	{
		player->levelUp();
	}


	return player->IsAlive();
}

/// <summary>
/// 
/// container = [ ?, ???�由, ?��?, 몃�?]
///                0      1      2     3
/// 
/// ��??��? �踰 1 ~ 4  : ?, ???�由
/// ��??��? �踰 5 ~ 8 : (?, ???�由) + 媛�?, ?��?
/// ��??��? �踰 9 ~ 10 : ?��?, 몃�?/// 
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
		// ?, ???�由 (0, 1)
		int idx = rand() % 2;	// 0 ~ 1
		result = Monsters[idx];
	}
	else if (playerLevel < 8)
	{
		// (?, ???�由) + 媛�?, ?��? (0,1,2)
		int idx = rand() % 3;	// 0 ~ 2
		result = Monsters[idx];
	}
	else
	{
		// ?��?, 몃�?(2,3)
		int idx = rand() % 2 + 2;	// 0 ~ 1
		result = Monsters[idx];
	}

	return result;
}

#pragma region Progress
// 寃�? 濡吏 �ㅼ�? ??
void GameManager::Progress()
{
	// 寃�? ?�猷 議곌�?: Player ?  ��??�댁 �踰?��? 10 誘몃?��?	bool bPlayerAlive = true;
	while (bPlayerAlive || Character::getInstance()->getLevel() < 10)
	{
		bPlayerAlive = Update();
	}

	// 寃�??�猷 濡吏 

}
#pragma endregion