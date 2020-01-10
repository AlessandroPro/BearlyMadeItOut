#include "Direction.h"
#include "GameManager.h"
#include <iostream>

void Direction::update()
{
	// block or unblock depending on the result of the item check
	bool shouldBeUnblocked = itemCheck.checkForItems();

	if (isBlocked && shouldBeUnblocked)
	{
		unBlock();
	}
	else if (!isBlocked && !shouldBeUnblocked)
	{
		block();
	}
}

void Direction::block()
{
	isBlocked = true;
	std::cout << blockMessage << std::endl;
}

void Direction::unBlock()
{
	isBlocked = false;
	std::cout << unblockMessage << std::endl;
	std::cout << "Now I can go " << name << "!";
}


void Direction::printDescription()
{
	if (isBlocked)
	{
		std::cout << blockedDesc << std::endl;
	}
	else
	{
		std::cout << unblockedDesc << std::endl;
	}
}

std::string& Direction::getConnectedLocation()
{
	return connectedLocation;
}

Location* Direction::onTravel()
{
	printDescription();
	if (isBlocked)
	{
		return nullptr;
	}
	return GameManager::Instance().getLocation(connectedLocation);
}

// Creates a new instance from the json object data, if it's a new game, will also set the dynamic data
GameObject* Direction::create(json::JSON& gameObjectNode, bool newGame)
{
	Direction* direction = new Direction();

	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	direction->setName(gameObjectNode["Name"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("ConnectedLocation"), "GameObject missing a ConnectedLocation!");
	direction->connectedLocation = gameObjectNode["ConnectedLocation"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("BlockedDesc"), "GameObject missing a BlockedDesc!");
	direction->blockedDesc = gameObjectNode["BlockedDesc"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("StartBlocked"), "GameObject missing a StartBlocked!");
	direction->isBlocked = gameObjectNode["StartBlocked"].ToBool();

	_ASSERT_EXPR(gameObjectNode.hasKey("BlockMessage"), "GameObject missing a BlockMessage!");
	direction->blockMessage = gameObjectNode["BlockMessage"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("UnblockedDesc"), "GameObject missing a UnblockedDesc!");
	direction->unblockedDesc = gameObjectNode["UnblockedDesc"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("UnblockMessage"), "GameObject missing a UnblockMessage!");
	direction->unblockMessage = gameObjectNode["UnblockMessage"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("PlayerCheckList"), "GameObject missing an PlayerCheckList!");
	direction->itemCheck.createPlayerItemList(gameObjectNode["PlayerCheckList"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocCheckList"), "GameObject missing an LocCheckList!");
	direction->itemCheck.createLocationItemList(gameObjectNode["LocCheckList"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string directionLocation = gameObjectNode["LocationName"].ToString();

	Location* location = GameManager::Instance().getLocation(directionLocation);


	if (location != nullptr)
	{
		location->addDirection(direction);
	}

	return direction;
}

json::JSON Direction::save(std::string& locationName)
{
	json::JSON object = json::JSON::Object();

	object["LocationName"] = locationName;
	object["Name"] = getName();
	object["IsBlocked"] = isBlocked;
	object["Type"] = "Direction";

	return object;
}

// Loads the dynamic data for the Direction instance and places it in the Location in which it belongs
void Direction::load(json::JSON& gameObjectNode)
{
	// Finds the Direction instance using the name and LocationName from the json node
	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	std::string name = gameObjectNode["Name"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string locationName = gameObjectNode["LocationName"].ToString();

	Location* location = GameManager::Instance().getLocation(locationName);

	// Loads the data of the found Direction Instance, if there is one.
	// Note: this is only data that can change for this object, static data is loaded in the create function
	if (location != nullptr)
	{
		Direction* direction = location->getDirection(name);
		
		if (direction != nullptr)
		{
			_ASSERT_EXPR(gameObjectNode.hasKey("StartBlocked"), "GameObject missing a StartBlocked!");
			direction->isBlocked = gameObjectNode["StartBlocked"].ToBool();
		}
	}
}

