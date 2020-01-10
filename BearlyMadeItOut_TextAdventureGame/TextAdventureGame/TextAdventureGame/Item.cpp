#include "Item.h"
#include <iostream>
#include "GameManager.h"
#include "InputManager.h"

Item::Item()
{
	inaccessibleDesc = "Can't pickup " + name + "It is inaccessible.";
	accessMessage = "The " + name + " can be picked up now.";
	inaccessMessage = "The " + name + " is now inaccessible.";
}

void Item::update()
{
	bool shouldBeAccessed = itemCheck.checkForItems();
	if (!isAccessible && shouldBeAccessed)
	{
		isAccessible = true;
		std::cout << accessMessage << std::endl;
	}
	else if (isAccessible && !shouldBeAccessed)
	{
		isAccessible = false;
		std::cout << inaccessMessage << std::endl;
	}
}

void Item::onAttack()
{
	std::cout << "Some scratches appear on the " << name << ". Probably shouldn't do that again." << std::endl;
}

void Item::onPickUp()
{
	if (isAccessible)
	{
		std::cout << "Picked up the " << name << "." << std::endl;
		GameManager::Instance().getPlayer()->addItem(this);
		GameManager::Instance().getPlayer()->getLocation()->removeItem(name);
	}
	else
	{
		std::cout << inaccessibleDesc << std::endl;
	}
}

void Item::onDrop()
{
	std::cout << "Dropped the " << name << "." << std::endl;
	GameManager::Instance().getPlayer()->removeItem(name);
	GameManager::Instance().getPlayer()->getLocation()->addItem(this);
}

void Item::setAccessible(bool accessible)
{
	isAccessible = accessible;
}

void Item::onSearch()
{
	std::cout << "Can't search " << name << "." << std::endl;
}

void Item::onHide()
{
	std::cout << "No need to hide that item." << std::endl;
}

// Creates a new instance from the json object data, if it's a new game, will also set the dynamic data
GameObject* Item::create(json::JSON& gameObjectNode, bool newGame)
{
	Item* item = new Item();

	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	item->setName(gameObjectNode["Name"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("InaccessibleDesc"), "GameObject missing an InaccessibleDesc!");
	item->inaccessibleDesc = gameObjectNode["InaccessibleDesc"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("AccessMessage"), "GameObject missing an AccessMessage!");
	item->accessMessage = gameObjectNode["AccessMessage"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("InaccessMessage"), "GameObject missing an InaccessMessage!");
	item->inaccessMessage = gameObjectNode["InaccessMessage"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("PlayerCheckList"), "GameObject missing a PlayerCheckList!");
	item->itemCheck.createPlayerItemList(gameObjectNode["PlayerCheckList"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocCheckList"), "GameObject missing a LocCheckList!");
	item->itemCheck.createLocationItemList(gameObjectNode["LocCheckList"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("StartWithoutAccess"), "GameObject missing a StartWithoutAccess!");
	item->isAccessible = !gameObjectNode["StartWithoutAccess"].ToBool();

	// Put the item in it's default location if a new game
	if (newGame)
	{
		_ASSERT_EXPR(gameObjectNode.hasKey("Owner"), "GameObject missing an Owner!");
		std::string itemOwner = InputManager::Instance().toUpper(gameObjectNode["Owner"].ToString());

		_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
		std::string itemLocation = gameObjectNode["LocationName"].ToString();

		Location* location = GameManager::Instance().getLocation(itemLocation);

		if (location != nullptr)
		{
			if (itemOwner.compare("LOCATION") == 0)
			{
				location->addItem(item);
			}
			else if (itemOwner.compare("SMALLSPACE") == 0)
			{
				if (location->smallSpace != nullptr)
				{
					location->smallSpace->addItem(item);
				}
			}
			else if (itemOwner.compare("GUARD") == 0)
			{
				if (location->guard != nullptr)
				{
					location->guard->setItem(item);
				}
			}
			else if (itemOwner.compare("PLAYER") == 0)
			{
				if (GameManager::Instance().getPlayer() != nullptr)
				{
					GameManager::Instance().getPlayer()->addItem(item);
				}
			}
		}
	}

	GameManager::Instance().addItem(item);
	return item;
}

void Item::load(json::JSON& gameObjectNode)
{
	_ASSERT_EXPR(gameObjectNode.hasKey("Owner"), "GameObject missing an Owner!");
	std::string itemOwner = InputManager::Instance().toUpper(gameObjectNode["Owner"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string itemLocation = gameObjectNode["LocationName"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	std::string itemName = gameObjectNode["Name"].ToString();

	Location* location = GameManager::Instance().getLocation(itemLocation);
	Item* item = GameManager::Instance().getItem(itemName);

	if (location != nullptr && item != nullptr)
	{
		if (itemOwner.compare("LOCATION") == 0)
		{
			location->addItem(item);
		}
		else if (itemOwner.compare("SMALLSPACE") == 0)
		{
			if (location->smallSpace != nullptr)
			{
				location->smallSpace->addItem(item);
			}
		}
		else if (itemOwner.compare("GUARD") == 0)
		{
			if (location->guard != nullptr)
			{
				location->guard->setItem(item);
			}
		}
		else if (itemOwner.compare("PLAYER") == 0)
		{
			if (GameManager::Instance().getPlayer() != nullptr)
			{
				GameManager::Instance().getPlayer()->addItem(item);
			}
		}
		_ASSERT_EXPR(gameObjectNode.hasKey("IsAccessible"), "GameObject missing a IsAccessible!");
		item->isAccessible = gameObjectNode["IsAccessible"].ToBool();
	}
}

json::JSON Item::save(std::string& locationName, std::string& owner)
{
	json::JSON object = json::JSON::Object();

	object["LocationName"] = locationName;
	object["Name"] = getName();
	object["Owner"] = owner;
	object["IsAccessible"] = isAccessible;
	object["Type"] = "Item";

	return object;
}


