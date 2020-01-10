#include "Clothing.h"
#include <iostream>
#include "GameManager.h"
#include "InputManager.h"


void Clothing::onPickUp()
{
	if (isAccessible)
	{
		std::cout << "Picked up and put on the " << name << ". Tight fit!" << std::endl;
		GameManager::Instance().getPlayer()->addItem(this);
		GameManager::Instance().getPlayer()->getLocation()->removeItem(name);
	}
	else
	{
		std::cout << inaccessibleDesc << std::endl;
	}

}

void Clothing::onDrop()
{
	std::cout << "Took off and dropped the " << name << "." << std::endl;
	GameManager::Instance().getPlayer()->removeItem(name);
	GameManager::Instance().getPlayer()->getLocation()->addItem(this);
}

// Creates a new instance from the json object data, if it's a new game, will also set the dynamic data
GameObject* Clothing::create(json::JSON& gameObjectNode, bool newGame)
{
	Clothing* item = new Clothing();

	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	item->setName(gameObjectNode["Name"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("InaccessibleDesc"), "GameObject missing an InaccessibleDesc!");
	item->inaccessibleDesc = gameObjectNode["InaccessibleDesc"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("AccessMessage"), "GameObject missing an AccessMessage!");
	item->accessMessage = gameObjectNode["AccessMessage"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("InaccessMessage"), "GameObject missing an InaccessMessage!");
	item->inaccessMessage = gameObjectNode["InaccessMessage"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("PlayerCheckList"), "GameObject missing an PlayerCheckList!");
	item->itemCheck.createPlayerItemList(gameObjectNode["PlayerCheckList"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocCheckList"), "GameObject missing an LocCheckList!");
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

void Clothing::load(json::JSON& gameObjectNode)
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
		item->setAccessible(gameObjectNode["IsAccessible"].ToBool());
	}


}

json::JSON Clothing::save(std::string& locationName, std::string& owner)
{
	json::JSON object = json::JSON::Object();

	object["LocationName"] = locationName;
	object["Name"] = getName();
	object["Owner"] = owner;
	object["IsAccessible"] = isAccessible;
	object["Type"] = "Clothing";

	return object;
}
