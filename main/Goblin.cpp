#include "Goblin.h"
#include <string>
//몬스터 스펙은 캐릭터 레벨에 비례해서 랜덤 생성 +- 1
// 체력 : 레벨x20 ~ 레벨 x 30
// 공격력 : 레벨 x 5 ~ 레벨 x 10
class Goblin : public Monster {
public :
	level += randomLV
	void getHealth() override {
		level * randomHP
	}
	void getAttack() override {
		level * randomAT
	}
};

