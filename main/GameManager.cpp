#include "GameManager.h"

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
void GameManager::Update()
{
	
}

#pragma region Progress
// 게임 로직 돌려주는 곳
void GameManager::Progress()
{
	// 게임 종료 조건 : Player 사망
	bool bPlayerAlive = true;
	while (bPlayerAlive)
	{
		Update();

		//bPlayerAlive = 플레이어로부터 체크;
	}

	// 게임종료 로직 수행

}
#pragma endregion