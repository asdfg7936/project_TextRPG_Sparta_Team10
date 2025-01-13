#include "Goblin.h"
#include <string>
//몬스터 스펙은 캐릭터 레벨에 비례해서 랜덤 생성 +- 1
// 체력 : 레벨x20 ~ 레벨 x 30
// 공격력 : 레벨 x 5 ~ 레벨 x 10
Goblin::Goblin(int level)
	:Monster(
		"고블린",
		(rand() % (level * 11)) + (level * 20),  //  체력
		(rand() % (level * 6)) + (level * 5),  //  공격
		level * 15 // 경험치
	) {}

void Goblin::TakeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

