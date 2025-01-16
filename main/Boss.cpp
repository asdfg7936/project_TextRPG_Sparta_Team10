#include "Boss.h"
#include <string>
#include <iostream>
#include "FileReaderManager.h"
#include "../Character/Character.h"

Boss::Boss(int level)
	:Monster(level,
		"오크 족장",
		4000, 150, 0)
{
	bMeet = true;
	bHpHalf = true;
	bAlmostDeath = true;
	bDeath = true;
}

void Boss::mTakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

void Boss::SoundEffect(float per)
{

	if (bMeet)
	{
		// comment
		std::cout << "===================" << std::endl;
		FRM->OpenFile(L"../story/BossStart.txt");
		FRM->PrintLineAll(Character::getInstance()->getName());
		FRM->CloseFile();
		std::cout << "===================" << std::endl;

		bMeet = false;
	}
	else if (bHpHalf && per <= 50)
	{
		// comment
		std::cout << "===================" << std::endl;
		FRM->OpenFile(L"../story/Boss50.txt");
		FRM->PrintLineAll(Character::getInstance()->getName());
		FRM->CloseFile();
		std::cout << "===================" << std::endl;

		bHpHalf = false;
	}
	else if (bAlmostDeath && per <= 20)
	{
		// comment
		std::cout << "===================" << std::endl;
		FRM->OpenFile(L"../story/Boss20.txt");
		FRM->PrintLineAll(Character::getInstance()->getName());
		FRM->CloseFile();
		std::cout << "===================" << std::endl;

		bAlmostDeath = false;
	}
	else if (bDeath && per <= 0)
	{
		// comment
		std::cout << "===================" << std::endl;
		FRM->OpenFile(L"../story/BossDead.txt");
		FRM->PrintLineAll(Character::getInstance()->getName());
		FRM->CloseFile();
		std::cout << "===================" << std::endl;

		bDeath = false;
	}
}
