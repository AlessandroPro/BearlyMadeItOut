#include "Guard.h"
#include <iostream>
#include "GameManager.h"

Guard::Guard()
{
	name = "Guard";
}

Guard::~Guard()
{
	if (item != nullptr)
	{
		delete item;
	}
}

void Guard::update()
{
}

// Called when a guard is alerted to the player's presence
void Guard::onAlert()
{
	std::cout << "The guard noticed you!" << std::endl;
	std::cout << "\"Hey you! How did you get out of your enclosure?!\"" << std::endl;
	Player* player = GameManager::Instance().getPlayer();
	player->tranquilze();
}

void Guard::dropItem()
{
	if (item != nullptr)
	{
		Location* location = GameManager::Instance().getPlayer()->getLocation();
		if (location != nullptr)
		{
			location->addItem(item);
			item = nullptr;
		}
	}
}

void Guard::setItem(Item* guardItem)
{
	if (guardItem != nullptr)
	{
		item = guardItem;
	}
}

Item* Guard::getItem()
{
	return item;
}

bool Guard::checkIsConscious()
{
	return isConscious;
}

void Guard::setConscious(bool conscious)
{
	isConscious = conscious;
}

void Guard::printStatus()
{
	if (isConscious)
	{
		std::cout << "A guard is patrolling the area...I should be careful with what I do." << std::endl;
	}
	else
	{
		std::cout << "An unconcious guard is on the floor." << std::endl;
	}
}

void Guard::onAttack()
{
	if (isConscious)
	{
		std::cout << "The guard fell to the ground. Scratched up pretty badly, and now unconcious." << std::endl;
		std::cout << "I probably shouldn't leave the body out here in the open." << std::endl;

		if (item != nullptr)
		{
			std::cout << " Oh, and perhaps I should search the body for something useful.";
		}
		std::cout << std::endl;
		isConscious = false;
	}
	else
	{
		std::cout << "The guard is already unconcious. No use doing more damage." << std::endl;
	}
}

void Guard::onPickUp()
{
	std::cout << "Can't pickup a human." << std::endl;
}

void Guard::onSearch()
{
	if (isConscious)
	{
		onAlert();
	}
	else
	{
		if (item != nullptr)
		{
			std::cout << "Pulled and dropped the guard's " << item->getName() << ". Looks like I can take this." << std::endl;
			dropItem();
		}
		else
		{
			std::cout << "The guard has nothing useful that I can take." << std::endl;
		}
		
	}
}

void Guard::onHide()
{
	if (isConscious)
	{
		onAlert();
	}
	else
	{
		Location* location = GameManager::Instance().getPlayer()->getLocation();
		SmallSpace* smallSpace = nullptr;

		if (location != nullptr)
		{
			smallSpace = location->getSmallSpace();
		}

		if (smallSpace != nullptr)
		{
			smallSpace->hideGuard(this);
			location->removeGuard();
			std::cout << "The guard was dragged and hidden in the " << smallSpace->getName() << "." << std::endl;
			if (item != nullptr)
			{
				std::cout << "While being shoved inside, their " << item->getName() << " dropped to the ground.";
				dropItem();
			}
		}
		else
		{
			std::cout << "Nowhere to hide the guard." << std::endl;
		}

	}
}

// Creates a new instance from the json object data, if it's a new game, will also set the dynamic data
GameObject* Guard::create(json::JSON& gameObjectNode, bool newGame)
{
	Guard* guard = new Guard();
	
	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	guard->setName(gameObjectNode["Name"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string guardLocation = gameObjectNode["LocationName"].ToString();

	Location* location = GameManager::Instance().getLocation(guardLocation);

	if (location != nullptr)
	{
		location->setGuard(guard);
	}

	return guard;
}

void Guard::load(json::JSON& gameObjectNode)
{
	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string locationName = gameObjectNode["LocationName"].ToString();

	_ASSERT_EXPR(gameObjectNode.hasKey("IsHidden"), "GameObject missing an IsHidden!");
	bool isHidden = gameObjectNode["IsHidden"].ToBool();

	Location* location = GameManager::Instance().getLocation(locationName);

	// Loads the data of the found guard Instance, if there is one.
	// Note: this is only data that can change for this object; static data is loaded in the create function
	if (location != nullptr)
	{
		Guard* guard = location->getGuard();

		if (guard != nullptr)
		{
			if (isHidden)
			{
				SmallSpace* smallSpace = location->getSmallSpace();
				if (smallSpace != nullptr)
				{
					location->removeGuard();
					smallSpace->hideGuard(guard);
				}
			}
			_ASSERT_EXPR(gameObjectNode.hasKey("IsConscious"), "GameObject missing an IsConscious!");
			guard->isConscious = gameObjectNode["IsConscious"].ToBool();

		}
	}
}

json::JSON Guard::save(std::string& locationName, bool hidden)
{
	json::JSON object = json::JSON::Object();
	
	Location* location = GameManager::Instance().getLocation(locationName);


	object["LocationName"] = locationName;
	object["IsConscious"] = isConscious;
	object["IsHidden"] = hidden;
	object["Type"] = "Guard";

	return object;
}
