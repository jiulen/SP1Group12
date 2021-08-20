#pragma once
#include "InGameItem.h"

class Inventory
{
private:
	InGameItem* items[8];

public:
	Inventory();
	~Inventory();
	InGameItem* GetInGameItems();
	void AddInGameItem();
};