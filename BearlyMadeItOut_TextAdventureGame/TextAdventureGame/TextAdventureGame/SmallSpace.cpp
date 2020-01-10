#include "SmallSpace.h"
#include <iostream>
#include "GameManager.h"

SmallSpace::~SmallSpace()
{
	for (auto& item : items)
	{
		if (item != nullptr)
		{
			delete item;
			item = nullptr;
		}
	}
	items.clear();

	if (hiddenGuard != nullptr)
	{
		delete hiddenGuard;
		hiddenGuard = nullptr;
	}
}

void SmallSpace::dropAllItems()
{
	for (const auto& item : items)
	{
		if (item != nullptr)
		{
			GameManager::Instance().getPlayer()->getLocation()->addItem(item);
		}
	}

	items.clear();
}

void SmallSpace::hideGuard(Guard* guard)
{
	hiddenGuard = guard;
}

void SmallSpace::addItem(Item* item)
{
	items.push_back(item);
}

Guard* SmallSpace::getGuard()
{
	return hiddenGuard;
}

const std::list<Item*>& SmallSpace::getItems()
{
	return items;
}

void SmallSpace::onAttack()
{
	std::cout << "Left some scratches on the " << name << ". No point in doing that again.";
}

void SmallSpace::onPickUp()
{
	std::cout << "Doesn't make sense to pick up the " << name << "." << std::endl;
}

void SmallSpace::onSearch()
{
	if (items.empty())
	{
		std::cout << "There's nothing in here.";
		if (hiddenGuard != nullptr)
		{
			std::cout << "..except for an unconcious guard.";
		}
	}
	else
	{
		if (hiddenGuard != nullptr)
		{
			std::cout << "The guard I hid in here is still unconcious. Nice." << std::endl;
		}
		std::cout << "Pulled out the following from the " << name << ":" << std::endl;

		for (const auto& item : items)
		{
			std::cout << item->getName() << std::endl;
		}
		dropAllItems();
	}
}

void SmallSpace::onHide()
{
	std::cout << "Doesn't make sense to hide the " << name << "." << std::endl;
}

// Creates a new instance from the json object data, if it's a new game, will also set the dynamic data
GameObject* SmallSpace::create(json::JSON& gameObjectNode, bool newGame)
{
	SmallSpace* smallSpace = new SmallSpace();

	_ASSERT_EXPR(gameObjectNode.hasKey("Name"), "GameObject missing a Name!");
	smallSpace->setName(gameObjectNode["Name"].ToString());

	_ASSERT_EXPR(gameObjectNode.hasKey("LocationName"), "GameObject missing a Location!");
	std::string smallSpaceLocation = gameObjectNode["LocationName"].ToString();

	Location* location = GameManager::Instance().getLocation(smallSpaceLocation);

	if (location != nullptr)
	{
		location->setSmallSpace(smallSpace);
	}

	return smallSpace;
}
