#include "Player.h"
#include <iostream>
#include "GameManager.h"
#include "Direction.h"
#include "InputManager.h"

Player::~Player()
{
	for (auto& itemKVPair : inventory)
	{
		if (itemKVPair.second != nullptr)
		{
			delete itemKVPair.second;
			itemKVPair.second = nullptr;
		}
	}
	inventory.clear();

	// Note that the allocated memory of the currentLocation
	// will be deleted in GameManager's destructor
}

//Places the player back in the startLocation
void Player::respawn()
{
	std::cout << "....\n....\n....That was a long sleep...\nLuckily it's still nighttime." << std::endl;
	stats.numRespawn++;
	changeLocation(startLocation);
	isTranquilized = false;
}

// Changes the current location to the locatioName's location
void Player::changeLocation(const std::string& locationName, bool onLoad)
{
	Location* newLocation = GameManager::Instance().getLocation(locationName);

	if (newLocation != nullptr)
	{
		currentLocation = newLocation;
		std::cout << std::endl << "Entering ";
		currentLocation->printDescription();

		//If changed to the end location, dispaly end message and lock commands
		if (currentLocation->nameAsUpper().compare(InputManager::Instance().toUpper(endLocation)) == 0 && !onLoad)
		{
			std::cout << endMessage << std::endl;
			GameManager::Instance().lockCommands = true;
		}
		// If the player left an unconcious guard in a location without hiding them, then
		// the next time they enter that location, the player will be caught (tranquilized)
		// and a new guard will take the old guard's place
		Guard* guard = currentLocation->getGuard();
		if (guard != nullptr && !onLoad)
		{
			if (!guard->checkIsConscious() && !isTranquilized)
			{
				guard->setConscious(true);
				std::cout << std::endl;
				std::cout << "Uh oh, there are several guards surrounding the guard I attacked earlier...I forgot to hide the body..." << std::endl;
				std::cout << "THEY SPOTTED ME! \"Hey! That's the bear! Get him!\" they yelled." << std::endl;
				tranquilze();
			}
		}
	}
	else
	{
		std::cout << "Location does not exist." << std::endl;
	}
}

// Tranquilizes the player (like player death)
void Player::tranquilze()
{
	std::cout << "You've been tranquilized! Lights out..." << std::endl;
	isTranquilized = true;
	dropAllItems();
	respawn();
}

// Checks if there is a conscious guard and alerts them if so
bool Player::guardCheck()
{
	Guard* guard = currentLocation->getGuard();
	if (guard != nullptr)
	{
		if (guard->checkIsConscious() && !isTranquilized)
		{
			guard->onAlert();
			return true;
		}
	}
	return false;
}

// Updates all game objects, including what the player has and what the current location has
void Player::update()
{
	for (const auto& itemKVPair : inventory)
	{
		Item* item = itemKVPair.second;
		if (item != nullptr)
		{
			item->update();
		}
	}

	if (currentLocation == nullptr)
	{
		return;
	}

	Guard* guard = currentLocation->getGuard();
	if ( guard != nullptr)
	{
		guard->update();
	}
	for (const auto& directionKVPair : currentLocation->getDirections())
	{
		Direction* direction = directionKVPair.second;
		if (direction != nullptr)
		{
			direction->update();
		}
	}

	for (const auto& itemKVPair : currentLocation->getItems())
	{
		Item* item = itemKVPair.second;
		if (item != nullptr)
		{
			item->update();
		}
	}
}

void Player::dropAllItems()
{
	std::cout << "All items dropped!" << std::endl;
	for (auto const& itemKVPair : inventory)
	{
		currentLocation->addItem(itemKVPair.second);
	}
	
	inventory.clear();
}

void Player::attack(const std::string& opponentName)
{
	IInteractable* opponent = nullptr;
	std::string oppNameUpper = InputManager::Instance().toUpper(opponentName);

	if (currentLocation != nullptr)
	{
		opponent = currentLocation->getInteractable(oppNameUpper);
	}

	if (opponent != nullptr)
	{
		opponent->onAttack();
		stats.numAttack++;
		if (guardCheck())
		{
			return;
		}
	}
	else
	{
		std::cout << "I probably shouldn't attack anything I'm unfamiliar with..." << std::endl;
	}
}

void Player::pickUp(const std::string& objectName)
{
	IInteractable* object = nullptr;

	std::string objNameUpper = InputManager::Instance().toUpper(objectName);

	if (currentLocation != nullptr)
	{
		object = currentLocation->getInteractable(objNameUpper);
	}

	if (object != nullptr)
	{
		object->onPickUp();
		stats.numPickup++;
		if (guardCheck())
		{
			return;
		}
	}
	else
	{
		std::cout << "I don't think that's something I could take with me..." << std::endl;
	}
}

void Player::drop(const std::string& objectName)
{
	Item* item = nullptr;
	std::string objNameUpper = InputManager::Instance().toUpper(objectName);

	item = inventory[objNameUpper];

	if (item != nullptr)
	{
		item->onDrop();
		stats.numDrop++;
	}
	else
	{
		std::cout << "I don't have any " << objectName << " to drop..." << std::endl;
	}
}

void Player::search(const std::string& objectName)
{
	IInteractable* object = nullptr;

	std::string objNameUpper = InputManager::Instance().toUpper(objectName);

	if (currentLocation != nullptr)
	{
		object = currentLocation->getInteractable(objNameUpper);
	}

	if (object != nullptr)
	{
		object->onSearch();
		stats.numSearch++;

		if (guardCheck())
		{
			return;
		}
	}
	else
	{
		std::cout << objectName << "? That's not something I can search..." << std::endl;
	}
}

void Player::hide(const std::string& objectName)
{
	IInteractable* object = nullptr;
	std::string objNameUpper = InputManager::Instance().toUpper(objectName);

	if (currentLocation != nullptr)
	{
		object = currentLocation->getInteractable(objNameUpper);
	}

	if (object != nullptr)
	{
		object->onHide();
		stats.numHide++;

		if (guardCheck())
		{
			return;
		}
	}
	else
	{
		std::cout << objectName << "? That's not something I would hide..." << std::endl;
	}
}

// Changes player location to the lcoation conencted to by the given direction, if valid
void Player::travel(const std::string& directionName)
{
	Direction* travelDirection = nullptr;
	Location* travelLocation = nullptr;

	std::string dirNameUpper = InputManager::Instance().toUpper(directionName);

	if (currentLocation != nullptr)
	{
		travelDirection = currentLocation->getDirection(dirNameUpper);
	}

	if (travelDirection != nullptr)
	{
		std::cout << "Heading " << travelDirection->getName() << "..." << std::endl;

		if (guardCheck())
		{
			return;
		}

		travelLocation = travelDirection->onTravel();
		stats.numTravel++;

		if (travelLocation != nullptr)
		{
			changeLocation(travelLocation->getName());
		}
		else
		{
			std::cout << "Can't go " << directionName << "...for now..." << std::endl;
		}
	}
	else
	{
		std::cout << "Hmm...that direction doesn't make sense here." << std::endl;
	}
}

void Player::load(json::JSON& gameObjectNode)
{
	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string locationName = gameObjectNode["LocationName"].ToString();

	GameManager::Instance().getPlayer()->changeLocation(locationName, true);
}

json::JSON Player::save()
{
	json::JSON object = json::JSON::Object();

	object["LocationName"] = currentLocation->getName();
	object["Type"] = "Player";

	return object;
}

void Player::addItem(Item* item)
{
	inventory.emplace(item->nameAsUpper(), item);
}

void Player::removeItem(const std::string& itemName)
{
	inventory.erase(InputManager::Instance().toUpper(itemName));
}

const std::map<std::string, Item*>& Player::getInventory()
{
	return inventory;
}

void Player::printInventory()
{
	if (inventory.empty())
	{
		std::cout << "Inventory is empty." << std::endl;
	}
	else
	{
		std::cout << "INVENTORY:" << std::endl;
		for (const auto& itemKVPair : inventory)
		{
			Item* item = itemKVPair.second;
			if (item != nullptr)
			{
				std::cout << item->getName() << std::endl;
			}
		}
	}
}

Location* Player::getLocation()
{
	return currentLocation;
}
