#include "Inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

InGameItem* Inventory::GetInGameItems()
{
	return (*items);
}

void Inventory::AddInGameItem(InGameItem& item)
{
	bool itemAdded = false;
	for (int i = 0; i < 8; i++)
	{
		if ((itemAdded == false) && (items[i] != nullptr))
		{
			(*items[i]) = item;
			itemAdded = true;
		}
	}
}