#pragma once

#ifndef GAMEMANGER_H
#define GAMEMANAGER_H

#include <map>
#include <string>
#include "Location.h"
#include "Player.h"
#include <functional>

// Singeton that maanges all game data, the game loop, and command processing
class GameManager
{
public:
	static GameManager& Instance();
	void destroy();

	void playGame();
	void processCommand(const std::string& command, const std::string& argument);
	Player* getPlayer();
	void setPlayer(Player* newPlayer);
	Location* getLocation(const std::string& locationName);
	void addLocation(Location* location);
	void addItem(Item* item);
	Item* getItem(const std::string& itemName);
	void initialize();
	void clearData();
	json::JSON saveData();
	void loadNewData(json::JSON document, bool newGame);
	void loadSaveData(json::JSON document);
	void printCommandList();

	bool lockCommands = true; // if true, only NEW, LOAD, and Q commands are accepted


private:

	explicit GameManager() = default;
	~GameManager();

	static GameManager* instance;

	std::map<std::string, Location*> locations;		// all locations in the world (each has a unique name)
	std::map<std::string, Item* > items;			// all items in the world (each has a unique name)
	std::list<GameObject*> gameObjects;
	std::map <std::string, std::function<GameObject* (json::JSON&, bool)>> createMap;
	std::map <std::string, std::function<void(json::JSON&)>> loadMap;
	std::map <std::string, std::function<void(std::string)>> playerActionsMap;
	Player* player = nullptr;

	inline explicit GameManager(GameManager const&) {};
	inline GameManager& operator=(GameManager const&) { return *this; };
};


#endif // !GAMEMANGER_H


