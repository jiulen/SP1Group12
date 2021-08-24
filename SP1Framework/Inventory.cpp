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
	items.push_back("Sword");
}

void Inventory::AddInGameItem(Chestplate& item)
{
	items.push_back("Chestplate");
}

void Inventory::AddInGameItem(Boot& item)
{
	items.push_back("Boot");
}

void Inventory::AddInGameItem(Potion& item)
{
	items.push_back("Potion");
}

/*void Inventory::RemoveItem(std::string& str)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == str)
		{
			items.erase(i);
		}
	}
}*/