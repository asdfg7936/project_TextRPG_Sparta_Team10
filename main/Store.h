#pragma once

#include <vector>

enum EItem
{
	Heal = 1,
	Strange,
};

class Store
{
private:
	static Store* instance;

	Store();
	~Store()
	{

	}

public:
	Store* getInstance()
	{
		if (nullptr == instance)
		{
			instance = new Store();
		}
		return instance;
	}

	void destroyInstance()
	{
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
	
private:
	std::vector<class Item*> items;
	class Character* player;

public:
	void buyStuff(int idx);
	void sellStuff(int idx);
};

/*
	vector<Stuff> inventory;
	idx_0 : heal
	idx_1 : strange

	����ü
		member_Item
		member_int cnt

	struct Stuff
	{
		Item* item;	// � ������?
		int cnt;	// ������ ����
	};

	int main()
	{
		Stuff s;
		s.item->getName();
		s.item->getQuantity();
		s.cnt;
	}
*/

