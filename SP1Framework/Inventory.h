#pragma once
#include "InGameItem.h"

class Inventory
{
private:
	InGameItem* items[8] = { nullptr, nullptr, nullptr, nullptr,nullptr, nullptr,nullptr, nullptr };

public:
	Inventory();
	~Inventory();
	InGameItem* GetInGameItems();
	void AddInGameItem(InGameItem&);
};