#pragma once

#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
#include "ItemCheck.h"
#include "GameObject.h"
#include "json.hpp"

class Location;

// Represents a direction that the player can go in from within a lcoation. Has a connected location. One way.
class Direction : public GameObject
{
private:
	std::string connectedLocation;
	bool isBlocked = false;

	std::string blockedDesc;
	std::string blockMessage;

	std::string unblockedDesc;
	std::string unblockMessage;

	ItemCheck itemCheck;

public:

	void update() override;
	void block();
	void unBlock();
	void printDescription();
	std::string& getConnectedLocation();
	Location* onTravel();

	static GameObject* create(json::JSON& gameObjectNode, bool newGame);
	static void load(json::JSON& gameObjectNode);
	json::JSON save(std::string& locationName);
};

#endif // !DIRECTION_H





