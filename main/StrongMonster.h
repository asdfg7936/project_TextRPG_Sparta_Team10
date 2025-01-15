#pragma once
#include "Monster.h"
#include <string>

class StrongMonster : public Monster {
private:
    Monster* baseMonster; // ���ڷ���Ʈ�� ���� ���� ��ü
    const int healthBonus = 300;
    const int attackBonus = 50;
    const int expBonus = 100;

public:
    // ������: ���ڷ����ʹ� ���� ���� ��ü�� �޾ƾ� ��
    explicit StrongMonster(Monster* monster)
        : Monster(monster->mGetLevel(), 
            "���� " + monster->mGetName(),
            monster->mGetMaxHealth() + healthBonus,
            monster->mGetAttack() + attackBonus,
            monster->mGetExp() + expBonus),
        baseMonster(monster) {
    }

    // �Ҹ���: ���� ���� ��ü�� ����
    ~StrongMonster() {
        delete baseMonster;
    }

    // �̸� �������̵�
    std::string mGetName() const override {
        return "���� " + baseMonster->mGetName();
    }

    // �ִ� ü��
    int mGetMaxHealth() const override {
        return baseMonster->mGetMaxHealth() + healthBonus;
    }

    // ���� ü��
    int mGetHealth() const override {
        return baseMonster->mGetHealth();
    }

    // ���ݷ�
    int mGetAttack() const override {
        return 3000 + baseMonster->mGetAttack() + attackBonus;
    }

    // ����ġ
    int mGetExp() const override {
        return baseMonster->mGetExp() + expBonus;
    }

    // ������ ó��
    void mTakeDamage(int damage) override {
        baseMonster->mTakeDamage(damage);
    }

    int mGetLevel() const override {
        return baseMonster->mGetLevel();
    }


};
