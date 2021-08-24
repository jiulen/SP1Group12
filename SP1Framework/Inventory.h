#pragma once
#include "InGameItem.h"
#include "Sword.h"
#include "Chestplate.h"
#include "Boot.h"
#include "Potion.h"

#include <string>
#include <vector>

class Inventory
{
private:
	std::vector<std::string> items;

public:
	Inventory();
	~Inventory();
	std::vector<std::string> GetInGameItems();
	void AddInGameItem(Sword&);
	void AddInGameItem(Chestplate&);
	void AddInGameItem(Boot&);
	void AddInGameItem(Potion&);
	//void RemoveItem(std::string&);
};