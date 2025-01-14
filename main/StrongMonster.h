#pragma once
#include "Monster.h"
#include <string>

class StrongMonster : public Monster {
private:
    Monster* baseMonster; // ���ڷ���Ʈ�� ���� ���� ��ü

public:
    // ������: ���ڷ����ʹ� ���� ���� ��ü�� �޾ƾ� ��
    explicit StrongMonster(Monster* monster)
        : Monster(monster->mGetLevel(), "���� " + monster->mGetName(),
            monster->mGetMaxHealth(), monster->mGetAttack(), monster->mGetExp()),
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
        return baseMonster->mGetMaxHealth();
    }

    // ���� ü��
    int mGetHealth() const override {
        return baseMonster->mGetHealth();
    }

    // ���ݷ�
    int mGetAttack() const override {
        return baseMonster->mGetAttack();
    }

    // ����ġ
    int mGetExp() const override {
        return baseMonster->mGetExp();
    }

    // ������ ó��
    void mTakeDamage(int damage) override {
        baseMonster->mTakeDamage(damage);
    }

    int mGetLevel() const override {
        return baseMonster->mGetLevel();
    }
};
