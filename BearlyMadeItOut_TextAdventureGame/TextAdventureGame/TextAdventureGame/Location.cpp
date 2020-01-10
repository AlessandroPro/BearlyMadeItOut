#include "Location.h"
#include <iostream>
#include "InputManager.h"
#include "GameManager.h"

Location::~Location()
{
	for (auto& itemKVPair : items)
	{
		if (itemKVPair.second != nullptr)
		{
			delete itemKVPair.second;
			itemKVPair.second = nullptr;
		}
	}
	items.clear();

	for (auto& directionKVPair : directions)
	{
		if (directionKVPair.second != nullptr)
		{
			delete directionKVPair.second;
			directionKVPair.second = nullptr;
		}
	}
	directions.clear();

	if (guard != nullptr)
	{
		delete guard;
		guard = nullptr;
	}

	if (smallSpace != nullptr)
	{
		delete smallSpace;
		smallSpace = nullptr;
	}

	// No need to delete IInteractable pointers, since all of their objects are 
	// stored and deleted in the maps above, and doing so would cause deletion at the same memory
	// address twice, which could be disastrous

}

void Location::addItem(Item* item)
{
	std::string itemNameUpper = item->nameAsUpper();
	items.emplace(itemNameUpper, item);
	interactables.emplace(itemNameUpper, item);
}

void Location::removeItem(const std::string& itemName)
{
	std::string itemNameUpper = InputManager::Instance().toUpper(itemName);
	items.erase(itemNameUpper);
	interactables.erase(itemNameUpper);
}

void Location::addDirection(Direction* direction)
{
	directions.emplace(direction->nameAsUpper(), direction);
}

Direction* Location::getDirection(const std::string& directionName)
{
	if (directions.find(directionName) != directions.end())
	{
		return directions[directionName];
	}
	else
	{
		return nullptr;
	}
}

IInteractable* Location::getInteractable(const std::string& interactableName)
{
	if (interactables.find(interactableName) != interactables.end())
	{
		return interactables[interactableName];
	}
	else
	{
		return nullptr;
	}
}

const std::map<std::string, Item*>& Location::getItems()
{
	return items;
}

const std::map<std::string, Direction*>& Location::getDirections()
{
	return directions;
}

void Location::setGuard(Guard* newGuard)
{
	guard = newGuard;
	interactables.emplace(newGuard->nameAsUpper(), newGuard);
}

void Location::removeGuard()
{
	if (guard != nullptr)
	{
		interactables.erase(guard->nameAsUpper());
		guard = nullptr;
	}
}

Guard* Location::getGuard()
{
	return guard;
}

void Location::setSmallSpace(SmallSpace* newSmallSpace)
{
	smallSpace = newSmallSpace;
	interactables.emplace(newSmallSpace->nameAsUpper(), newSmallSpace);
}

SmallSpace* Location::getSmallSpace()
{
	return smallSpace;
}

void Location::printDescription()
{
	std::cout << nameAsUpper() << ":" << std::endl;
	std::cout << description << std::endl;



	if (smallSpace != nullptr)
	{
		std::cout << "There is a " << smallSpace->getName() << "." << std::endl;
	}

	if (guard != nullptr)
	{
		guard->printStatus();
	}


	if (!items.empty())
	{
		std::cout << "Laying around, you can see:" << std::endl;

		for (auto it = items.begin(); it != items.end(); it++)
		{
			Item* item = it->second;
			if (item != nullptr)
			{
				std::cout << item->getName();

				auto lastItemIter = items.end();
				lastItemIter--;
				if (it != lastItemIter)
				{
					std::cout << std::endl;
				}
			}
		}
		std::cout << std::endl;
	}
}

void Location::printDirections()
{

	std::cout << std::endl << "Directions in this location:" << std::endl;
	if (directions.empty())
	{
		std::cout << "There are no directions in this location." << std::endl;
		return;
	}
	
	for (auto& directionKVPair : directions)
	{
		if (directionKVPair.second != nullptr)
		{
			std::cout << directionKVPair.second->getName() << " to ";
			std::cout << directionKVPair.second->getConnectedLocation() << std::endl;
		}
	}
}


// Creates a new instance from the json object data, if it's a new game, will also set the dynamic data
GameObject* Location::create(json::JSON& gameObjectNode, bool newGame)
{
	Location* location = new Location();

	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	location->setName(gameObjectNode["Name"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("Description"), "GameObject missing a Description!");
	location->description = (gameObjectNode["Description"].ToString());

	GameManager::Instance().addLocation(location);

	return location;
}


