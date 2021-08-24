#include "Inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

std::vector<std::string> Inventory::GetInGameItems()
{
	return items;
}

void Inventory::AddInGameItem(Sword& item)
{
	if (items.size() < 10) { items.push_back("Sword"); }
}

void Inventory::AddInGameItem(Chestplate& item)
{
	if (items.size() < 10) { items.push_back("Chestplate"); }
}

void Inventory::AddInGameItem(Boot& item)
{
	if (items.size() < 10) { items.push_back("Boot"); }
}

void Inventory::AddInGameItem(Potion& item)
{
	if (items.size() < 10) { items.push_back("Potion"); }
}

void Inventory::RemoveItem(std::string str)
{
	for (unsigned i = 0; i < items.size(); i++)
	{
		if (items[i] == str)
		{
			items.erase(items.begin() + i);
			break;
		}
	}
}