#pragma once
#ifndef ITEMCHECK_H
#define ITEMCHECK_H

#include <list>
#include <string>
#include <map>
class Item;

// Used to check if a set of items exists within the player's inventory and/or the currently location
class ItemCheck
{
protected:

	std::list<std::string> locationItemNames;	// location item name to check for
	std::list<std::string> playerItemNames;		// Player item names to check for
	bool autoSuccess = false;					// if true, item check will always return successful

public:

	ItemCheck() = default;
	~ItemCheck() = default;

	bool checkForItems();
	void addToLocationItemList(const std::string& itemName);
	void addToPlayerItemList(const std::string& itemName);
	void createLocationItemList(const std::string& itemList);
	void createPlayerItemList(const std::string& itemList);
};


#endif // !ITEMCHECK_H



