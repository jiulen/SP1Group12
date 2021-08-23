#include "Inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

InGameItem** Inventory::GetInGameItems()
{
	return items;
}

void Inventory::AddInGameItem(InGameItem* item)
{
	for (unsigned i = 0; i < 8; i++)
	{
		if (items[i] == nullptr)
		{
			items[i] = item;
			break;
		}
	}
}