#include "GameManager.h"
#include <iostream>
#include "InputManager.h"
#include "FileManager.h"
#include "DatabaseManager.h"
#include <windows.h>

GameManager* GameManager::instance = nullptr;


GameManager::~GameManager()
{
	clearData();
	// Poniters in this instances gameobjects and items maps are not deleted here, but within the objects that own them
}

// Clears all data for this instance (all locations, the player, items, etc). Used before when loading a new game.
void GameManager::clearData()
{
	if (player != nullptr)
	{
		delete player;
	}

	for (const auto& locationKVPair : locations)
	{
		Location* location = locationKVPair.second;
		if (location != nullptr)
		{
			delete location;
		}
	}

	gameObjects.clear();
	locations.clear();
	items.clear();
}

// Loops through the hiearchy of gameObjects and saves each gameObject's dynamic data as a json object
// which is then added to an array of objects that gets returned as one json object 
// The location of each game object is also recorded for easy loading
json::JSON GameManager::saveData()
{

	json::JSON document;
	json::JSON objectData;
	int i = 0;

	std::cout << "Saving game..." << std::endl;
	for (const auto& locationKVPair : locations)
	{
		Location* location = locationKVPair.second;
		if (location != nullptr)
		{
			std::string locationName = location->getName();
			for (const auto& directionKVPair : location->getDirections())
			{
				Direction* direction = directionKVPair.second;
				if (direction != nullptr)
				{
					objectData[i++] = direction->save(locationName);
				}
			}
			for (const auto& itemKVPair : location->getItems())
			{
				Item* item = itemKVPair.second;
				if (item != nullptr)
				{
					std::string owner = "LOCATION";
					objectData[i++] = item->save(locationName, owner);
				}
			}
			if (location->guard != nullptr)
			{
				objectData[i++] = location->guard->save(locationName, false);
				if (location->guard->getItem() != nullptr)
				{
					std::string owner = "GUARD";
					objectData[i++] = location->guard->getItem()->save(locationName, owner);
				}
			}
			if (location->smallSpace != nullptr)
			{
				if (location->smallSpace->getGuard() != nullptr)
				{
					objectData[i++] = location->smallSpace->getGuard()->save(locationName, true);
				}
				for (const auto& item : location->smallSpace->getItems())
				{
					if (item != nullptr)
					{
						std::string owner = "SMALLSPACE";
						objectData[i++] = item->save(locationName, owner);
					}
				}
			}
		}
	}
	for (const auto& itemKVPair : player->getInventory())
	{
		Item* item = itemKVPair.second;
		if (item != nullptr)
		{
			std::string currentLocName = player->getLocation()->getName();
			std::string owner = "PLAYER";
			objectData[i++] = item->save(currentLocName, owner);
		}
	}

	if (player != nullptr)
	{
		objectData[i++] = player->save();
	}

	document["GameObjects"] = objectData;

	return document;
}

// Clears all game data and loads new data from the json document, which 
// should contain all of the default info for a game (this file should be created in a tool)
// If a new game, objects will only load their static data 
void GameManager::loadNewData(json::JSON document, bool newGame)
{
	clearData();

	Player* player = new Player();
	setPlayer(player);

	lockCommands = false;

	std::cout << std::endl << "Loading game..." << std::endl << std::endl;
	
	_ASSERT_EXPR(document.hasKey("StartLocation"), "Document missing StartLocation!");
	std::string startLoc = document["StartLocation"].ToString();
	player->startLocation = startLoc;

	_ASSERT_EXPR(document.hasKey("EndLocation"), "Document missing EndLocation!");
	std::string endLoc = document["EndLocation"].ToString();
	player->endLocation = endLoc;

	_ASSERT_EXPR(document.hasKey("StartMessage"), "Document missing StartMessage!");
	std::string startMessage = document["StartMessage"].ToString();
	player->startMessage = startMessage;

	_ASSERT_EXPR(document.hasKey("EndMessage"), "Document missing EndMessage!");
	std::string endMessage = document["EndMessage"].ToString();
	player->endMessage = endMessage;

	_ASSERT_EXPR(document.hasKey("GameObjects"), "Document missing GameObjects!");
	json::JSON gameObjectsNode = document["GameObjects"];

	for (auto& gameObjectNode : gameObjectsNode.ArrayRange())
	{
		_ASSERT_EXPR(gameObjectNode.hasKey("Type"), "GameObject missing type!");
		std::string gameObjectType = gameObjectNode["Type"].ToString();

		// Creates game objects based on function pointers to their respective classes
		if (createMap.find(gameObjectType) != createMap.end())
		{
			GameObject* gameObject = createMap[gameObjectType](gameObjectNode, newGame);
			gameObjects.push_back(gameObject);
		}
	}

	if (getLocation(player->startLocation) == nullptr)
	{
		std::cerr << "Invalid start location specified. Exiting." << std::endl;
		exit(-1);
	}

	// Only in a new game will the player start message dispaly
	if (newGame)
	{
		std::cout << player->startMessage << std::endl;
		player->changeLocation(player->startLocation, true);
	}
}

// Updates all game objects' dynamic data with the save file data in the json document
void GameManager::loadSaveData(json::JSON document)
{
	_ASSERT_EXPR(document.hasKey("GameObjects"), "Document missing GameObjects!");
	json::JSON gameObjectsNode = document["GameObjects"];

	for (auto& gameObjectNode : gameObjectsNode.ArrayRange())
	{
		_ASSERT_EXPR(gameObjectNode.hasKey("Type"), "GameObject missing type!");
		std::string gameObjectType = gameObjectNode["Type"].ToString();

		if (loadMap.find(gameObjectType) != loadMap.end())
		{
			loadMap[gameObjectType](gameObjectNode);
		}
	}
}

// Dispalys all possible commands to the user
void GameManager::printCommandList()
{
	std::cout << "List of Commands:" << std::endl << std::endl;
	std::cout << "Go [Direction]" << std::endl;
	std::cout << "Pickup [x] | Take [x]" << std::endl;
	std::cout << "Attack [x]" << std::endl;
	std::cout << "Drop [x]" << std::endl;
	std::cout << "Search [x]" << std::endl;
	std::cout << "Hide [x]" << std::endl << std::endl;
	std::cout << "Look" << std::endl;
	std::cout << "Inventory" << std::endl;
	std::cout << "Help" << std::endl;
	std::cout << "New" << std::endl;
	std::cout << "Save" << std::endl;
	std::cout << "Load" << std::endl;
	std::cout << "Q to quit the game" << std::endl << std::endl;
}

GameManager& GameManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new GameManager;
	}
	return *instance;
}

void GameManager::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//Game Loop
// Processes commands from user input
void GameManager::playGame()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);

	std::cout << "*****************************************" << std::endl;
	std::cout << "Welcome to 'Bearly Made It Out'!" << std::endl;
	std::cout << "*****************************************" << std::endl << std::endl;
	std::cout << "LOAD or NEW game?" << std::endl << std::endl;
	while (true)
	{
		std::pair<std::string, std::string> command = InputManager::Instance().getCommand();
		if (command.first.compare("Q") == 0 && command.second.empty())
		{
			DatabaseManager::Instance().logPlayerStats(player->stats);
			break;
		}
		std::cout << std::endl;
		processCommand(command.first, command.second);
		std::cout << std::endl;
	}
}

// Processes the command given by the player (the first word), along with its argument
// then updates all game objects
void GameManager::processCommand(const std::string& command, const std::string& argument)
{
	if (command.empty() && argument.empty())
	{
		std::cout << "Please enter a command:" << std::endl;
		return;
	}

	if (playerActionsMap.find(command) != playerActionsMap.end() && !lockCommands)
	{
		if (argument.empty())
		{
			std::cout << "Incomplete command." << std::endl;
		}
		else
		{
			// Maps to a player action function, depending on the provided command
			playerActionsMap[command](argument);
		}
	}
	else if(argument.empty())
	{
		if (command.compare("INVENTORY") == 0 && !lockCommands)
		{
			player->printInventory();
		}
		else if (command.compare("LOOK") == 0 && !lockCommands)
		{
			player->getLocation()->printDescription();
		}
		else if (command.compare("HELP") == 0 && !lockCommands)
		{
			printCommandList();
			player->getLocation()->printDirections();
		}
		else if (command.compare("SAVE") == 0 && !lockCommands)
		{
			FileManager::Instance().saveFile(saveData());
		}
		else if (command.compare("NEW") == 0)
		{
			loadNewData(FileManager::Instance().loadNewFile(), true);
		}
		else if (command.compare("LOAD") == 0)
		{
			loadNewData(FileManager::Instance().loadNewFile(), false);
			loadSaveData(FileManager::Instance().loadSaveFile());
		}
		else
		{
			std::cout << "I don't know what that means...Invalid command." << std::endl;
		}
	}
	else
	{
		std::cout << "I don't know what that means...Invalid command." << std::endl;
	}
	
	player->update();
}

//Returns the player
Player* GameManager::getPlayer()
{
	return player;
}

// Sets the player and rebinds the player action function points with the given player instance
void GameManager::setPlayer(Player* newPlayer)
{
	player = newPlayer;

	playerActionsMap.clear();

	using std::placeholders::_1;
	playerActionsMap.emplace("GO", std::bind(&Player::travel, player, _1));
	playerActionsMap.emplace("ATTACK", std::bind(&Player::attack, player, _1));
	playerActionsMap.emplace("PICKUP", std::bind(&Player::pickUp, player, _1));
	playerActionsMap.emplace("TAKE", std::bind(&Player::pickUp, player, _1));
	playerActionsMap.emplace("DROP", std::bind(&Player::drop, player, _1));
	playerActionsMap.emplace("SEARCH", std::bind(&Player::search, player, _1));
	playerActionsMap.emplace("HIDE", std::bind(&Player::hide, player, _1));
}

// Returns a location from the lcoation map, if one with lcoation name exists
Location* GameManager::getLocation(const std::string& locationName)
{
	std::string locationNameUpper = InputManager::Instance().toUpper(locationName);
	if (locations.find(locationNameUpper) != locations.end())
	{
		return locations[locationNameUpper];
	}
	return nullptr;
}

// Adds location to the location map
void GameManager::addLocation(Location* location)
{
	if (location != nullptr)
	{
		locations.emplace(location->nameAsUpper(), location);
	}
}

// Adds item to the item map
void GameManager::addItem(Item* item)
{
	if (item != nullptr)
	{
		items.emplace(item->nameAsUpper(), item);
	}
}

// Returns the item with itemName if it exists
Item* GameManager::getItem(const std::string& itemnName)
{
	std::string itemNameUpper = InputManager::Instance().toUpper(itemnName);
	if (items.find(itemNameUpper) != items.end())
	{
		return items[itemNameUpper];
	}
	return nullptr;
}


// Create the player and fill the function pointer maps
void GameManager::initialize()
{
	Player* player = new Player();
	setPlayer(player);

	createMap.emplace("Location", &Location::create);
	createMap.emplace("Item", &Item::create);
	createMap.emplace("Clothing", &Clothing::create);
	createMap.emplace("Direction", &Direction::create);
	createMap.emplace("SmallSpace", &SmallSpace::create);
	createMap.emplace("Guard", &Guard::create);

	loadMap.emplace("Item", &Item::load);
	loadMap.emplace("Clothing", &Clothing::load);
	loadMap.emplace("Direction", &Direction::load);
	loadMap.emplace("Guard", &Guard::load);
	loadMap.emplace("Player", &Player::load);
}
