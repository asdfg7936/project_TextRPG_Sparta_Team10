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
/// 한글 테스트
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
/// 게임 시작전 초기화 해야하는 것들 추가
/// ex) 플레이어 캐릭터 생성, 등...
/// </summary>
void GameManager::Init()
{
	// 플레이어 이름 입력
	std::string playerName = "";
	std::cout << "플레이어의 이름을 입력하세요 : ";
	std::cin >> playerName;
	Character::getInstance(playerName);
	std::cout << playerName;	// debug

	// 초반 스토리 출력
	FileReaderManager* FRM = FileReaderManager::GetInstance();
	FRM->OpenFile("../test.txt");
	FRM->CloseFile();

	// 플레이어 레벨 2로 설정하고 시작
	Character::getInstance()->levelUp();
}

/// <summary>
/// 게임 로직
/// 
/// 한 턴동안 발생해야하는 모든 것
///	ex)
///		플레이어 입력 (공격? 스킬? 아이템? 상점?)
///		플레이어의 입력값에 따른 상호작용
///			case1 : 플레이어가 몬스터를 공격했다.
///			case2 : 플레이어가 스킬을쓴다 -> MP 부족하다
///			case3 : 아이템을 사용했다 -> 그에따른 효과
///			case4 : 상점 NPC 만났다 -> 아이템 사야하는데 돈이 부족하다. 구매했다.
///		플레이어 or 몬스터가 죽음
///			case1 : 플레이어 죽음 -> 게임 끝 (로그라이크)
///			case2 : 몬스터가 죽었다 -> 경험치, 아이템 드랍 -> 레벨업 or 장비를 갈아낄수도있고 or 이벤트발생
///		목적지 or 다음 진행을 위한 선택 
/// 
/// </summary>

/// <summary>
/// 
/// 몬스터 : 늑대, 고블린, 오크, 트롤
///	 
/// 플레이어 레벨 1 ~ 4  : 늑대, 고블린
/// 플레이어 레벨 5 ~ 8 : (늑대, 고블린) + 강한, 오크
/// 플레이어 레벨 9 ~ 10 : 오크, 트롤
/// 
/// </summary>
bool GameManager::Update()
{
	Character* player = Character::getInstance();

	//몬스터 생성
	Monster* genMonster = GenMonster(Character::getInstance()->getLevel());

	// enter 입력 -> 한턴
	int Select = 0;	// true : 상점
	std::cout << "무엇을 하시겠습니까?" << std::endl;
	std::cout << "1번 : 상점" << std::endl;
	std::cout << "2번 : 능력치 확인" << std::endl;
	std::cout << "3번 : 전투 시작" << std::endl;
	std::cin >> Select;

	// 상점을 들리게 된다면 -> 템 사는거 내가 선택해서 구매 (템 : 물약, 수상한 물약)
	if(1 == Select)
	{
		// 아이템 목록 출력
		 
		// 아이템 선택 및 구매

		// 구매 완료 후 상점 탈출
	}

	if (2 == Select)
	{
		player->displayStatus();
	}

	if (3 == Select)
	{
		
		std::cout << "야생의 " << genMonster->mGetName() << "이(가) 출몰했습니다.\n";
		//몬스터 스텟 출력
		//genMonster->displayStatus();
		// 전투
		// 몬스터의 체력이 0 초과 이고 플레이어가 살아있을 때
		while (genMonster->mGetHealth() > 0 && player->IsAlive())
		{
			//std::cin.get();  //  enter 치면 턴 넘기기
			// if(체력이 50% 이하면 && 체력 물약 소지하고 있으면)
			// {
			//	체력 물약을 사용한다.
			// }
			// else if(수상한 물약을 소지하고 있으면)
			// {
			//	30% 확률로 사용
			// }
			// else
			// {
			//	공격
			genMonster->mTakeDamage(player->getAttack());
			std::cout << player->getName() << "이(가) " << genMonster->mGetName() << "을(를) 공격했습니다." << std::endl;
			std::cout << genMonster->mGetName() << "은(는) " << player->getAttack() << "만큼 대미지를 입었습니다." << std::endl;
			// }

			// 몬스터가 플레이어 공격
			player->TakeDamage(genMonster->mGetAttack());
			std::cout << genMonster->mGetName() << "이(가) " << player->getName() << "을(를) 공격했습니다." << std::endl;
			std::cout << player->getName() << "은(는) " << genMonster->mGetAttack() << "만큼 대미지를 입었습니다." << std::endl;
		}
	}

	// 몬스터가 죽은 경우
	if (genMonster->mGetHealth() <= 0)
	{
		std::cout << genMonster->mGetName() << "이(가) 죽었습니다." << std::endl;
		std::cout << "다음 보상을 획득했습니다." << std::endl;
		// 몬스터가 죽으면? -> 경험치/골드 획득
		int rndGold = rand() % 11 + 10;
		player->setGold(player->getGold() + rndGold);
		std::cout << rndGold << " 골드 획득" << std::endl;
		if (player->getLevel() < 10)
		{
			player->setExperience(player->getExperience() + genMonster->mGetExp());
			std::cout << genMonster->mGetExp() << " 경험치 획득" << std::endl;
		}

	}

	//레벨업 체크
	if (player->getExperience() >= player->getExperienceToNextLevel() && player->getLevel() < 10)
	{
		player->levelUp();
	}


	return player->IsAlive();
}

/// <summary>
/// 
/// container = [ 늑대, 고블린, 오크, 트롤 ]
///                0      1      2     3
/// 
/// 플레이어 레벨 1 ~ 4  : 늑대, 고블린
/// 플레이어 레벨 5 ~ 8 : (늑대, 고블린) + 강한, 오크
/// 플레이어 레벨 9 ~ 10 : 오크, 트롤
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
		// 늑대, 고블린 (0, 1)
		int idx = rand() % 2;	// 0 ~ 1
		result = Monsters[idx];
	}
	else if (playerLevel < 8)
	{
		// (늑대, 고블린) + 강한, 오크 (0,1,2)
		int idx = rand() % 3;	// 0 ~ 2
		result = Monsters[idx];
	}
	else
	{
		// 오크, 트롤 (2,3)
		int idx = rand() % 2 + 2;	// 0 ~ 1
		result = Monsters[idx];
	}

	return result;
}

#pragma region Progress
// 게임 로직 돌려주는 곳
void GameManager::Progress()
{
	// 게임 종료 조건 : Player 사망 또는 플레이어의 레벨이 10 미만일때
	bool bPlayerAlive = true;
	while (bPlayerAlive || Character::getInstance()->getLevel() < 10)
	{
		bPlayerAlive = Update();
	}

	// 게임종료 로직 수행

}
#pragma endregion