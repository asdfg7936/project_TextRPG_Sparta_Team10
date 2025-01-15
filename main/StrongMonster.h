#pragma once
#include "Monster.h"
#include <string>

class StrongMonster : public Monster {
private:
    Monster* baseMonster; // 데코레이트할 기존 몬스터 객체
    const int healthBonus = 300;
    const int attackBonus = 50;
    const int expBonus = 100;

public:
    // 생성자: 데코레이터는 기존 몬스터 객체를 받아야 함
    explicit StrongMonster(Monster* monster)
        : Monster(monster->mGetLevel(), 
            "강한 " + monster->mGetName(),
            monster->mGetMaxHealth() + healthBonus,
            monster->mGetAttack() + attackBonus,
            monster->mGetExp() + expBonus),
        baseMonster(monster) {
    }

    // 소멸자: 내부 몬스터 객체도 삭제
    ~StrongMonster() {
        delete baseMonster;
    }

    // 이름 오버라이딩
    std::string mGetName() const override {
        return "강한 " + baseMonster->mGetName();
    }

    // 최대 체력
    int mGetMaxHealth() const override {
        return baseMonster->mGetMaxHealth() + healthBonus;
    }

    // 현재 체력
    int mGetHealth() const override {
        return baseMonster->mGetHealth();
    }

    // 공격력
    int mGetAttack() const override {
        return 3000 + baseMonster->mGetAttack() + attackBonus;
    }

    // 경험치
    int mGetExp() const override {
        return baseMonster->mGetExp() + expBonus;
    }

    // 데미지 처리
    void mTakeDamage(int damage) override {
        baseMonster->mTakeDamage(damage);
    }

    int mGetLevel() const override {
        return baseMonster->mGetLevel();
    }


};
