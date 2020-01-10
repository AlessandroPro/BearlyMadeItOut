#include "ItemCheck.h"
#include "GameManager.h"
#include "InputManager.h"
#include <sstream>


// Returns true if the current location has all of the items in the locationItemList
// and if the player's inventory has all of the items in the playerItemList, false otherwise
bool ItemCheck::checkForItems()
{
	if (autoSuccess)
	{
		return true;
	}

	Player* player = GameManager::Instance().getPlayer();

	const auto& playerItems = player->getInventory();
	const auto& locationItems = player->getLocation()->getItems();

	for(const std::string& itemName : locationItemNames)
	{
		if (locationItems.find(itemName) == locationItems.end())
		{
			return false;
		}
	}

	for (const std::string& itemName : playerItemNames)
	{
		if (playerItems.find(itemName) == playerItems.end())
		{
			return false;
		}
	}

	autoSuccess = true;
	return true;
}

// Parses a comma delimeted string that is a list of item names.
// Extracts the names and adds them to the itemList.
void ItemCheck::createLocationItemList(const std::string& itemList)
{
	locationItemNames.clear();
	std::stringstream ss(itemList);

	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		
		//Remove trailing and leading whitespaces from the item name
		size_t p = substr.find_first_not_of(" ");
		substr.erase(0, p);

		p = substr.find_last_not_of(" ");
		if (std::string::npos != p)
		{
			substr.erase(p + 1);
		}

		if (substr.length() > 0)
		{
			addToLocationItemList(substr);
		}
	}
}

// Parses a comma delimeted string that is a list of item names.
// Extracts the names and adds them to the itemList.
void ItemCheck::createPlayerItemList(const std::string& itemList)
{
	playerItemNames.clear();
	std::stringstream ss(itemList);

	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');

		//Remove trailing and leading whitespaces from the item name
		size_t p = substr.find_first_not_of(" ");
		substr.erase(0, p);

		p = substr.find_last_not_of(" ");
		if (std::string::npos != p)
		{
			substr.erase(p + 1);
		}

		if (substr.length() > 0)
		{
			addToPlayerItemList(substr);
		}
	}
}

void ItemCheck::addToLocationItemList(const std::string& itemName)
{
	locationItemNames.push_back(InputManager::Instance().toUpper(itemName));
}

void ItemCheck::addToPlayerItemList(const std::string& itemName)
{
	playerItemNames.push_back(InputManager::Instance().toUpper(itemName));
}
