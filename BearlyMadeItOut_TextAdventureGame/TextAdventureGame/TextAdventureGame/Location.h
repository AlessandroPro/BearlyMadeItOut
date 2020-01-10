#pragma once

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include "IInteractable.h"
#include "Guard.h"
#include "Item.h"
#include "Direction.h"
#include "SmallSpace.h"
#include "json.hpp"

// Represents a lcoation in the game, which can be entered and exited by the player, 
// has directions and items and possibly a guard and small space
class Location : public GameObject
{
private:
	std::string description;
	std::map<std::string, IInteractable*> interactables;
	std::map<std::string, Direction*> directions;
	std::map<std::string, Item*> items;

public:

	Guard* guard = nullptr;
	SmallSpace* smallSpace = nullptr;

	Location() = default;
	~Location();
	void addItem(Item* item);
	void removeItem(const std::string& itemName);
	void addDirection(Direction* direction);
	Direction* getDirection(const std::string& directionName);
	IInteractable* getInteractable(const std::string& interactableName);
	const std::map<std::string, Item*>& getItems();
	const std::map<std::string, Direction*>& getDirections();
	void setGuard(Guard* newGuard);
	void removeGuard();
	Guard* getGuard();
	void setSmallSpace(SmallSpace* newSmallSpace);
	SmallSpace* getSmallSpace();
	void printDescription();
	void printDirections();
	
	static GameObject* create(json::JSON& gameObjectNode, bool newGame);
};

#endif // !LOCATION_H



