#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <string>
#include "Location.h"
#include "Clothing.h"

// Staticstics for frequency of player actions
struct PlayerActionStats
{
	int numTravel = 0;
	int numAttack = 0;
	int numPickup = 0;
	int numDrop = 0;
	int numSearch = 0;
	int numHide = 0;
	int numRespawn = 0;
};

// A Player within the game
class Player : public GameObject
{
private:
	Location* currentLocation = nullptr;
	std::map<std::string, Item*> inventory;
	bool isTranquilized = false;

public:

	PlayerActionStats stats;
	std::string startLocation;
	std::string endLocation;
	std::string startMessage;
	std::string endMessage;

	Player() = default;
	~Player();
	void respawn();
	void dropAllItems();
	void addItem(Item* item);
	void removeItem(const std::string& itemName);
	const std::map<std::string, Item*>& getInventory();
	void printInventory();
	Location* getLocation();
	void changeLocation(const std::string& locationName, bool onLoad = false);
	void tranquilze();
	bool guardCheck();
	void update() override;

	void attack(const std::string& objectName);
	void pickUp(const std::string& objectName);
	void drop(const std::string& objectName);
	void search(const std::string& objectName);
	void hide(const std::string& objectName);
	void travel(const std::string& directionName);

	static void load(json::JSON& gameObjectNode);
	json::JSON save();
};



#endif // !PLAYER_H

