#include "FileManager.h"
#include "json.hpp"
#include <fstream>
#include "GameManager.h"

FileManager* FileManager::instance = nullptr;

FileManager& FileManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new FileManager();
	}
	return *instance;
}

void FileManager::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// Saves the json document to a specific file. This data is the saved state of the game, and is needed for loading.
void FileManager::saveFile(const json::JSON& document)
{
	try
	{
		std::ofstream ostrm("../Assets/SaveData/gameSaveData.json");
		ostrm << document.dump();
		ostrm.close();
	}
	catch(...)
	{
		std::cout << "Error saving json file. Save aborted." << std::endl;
	}
}

// Loads the json file created by the data entry tool. This data is used to create all objects in the game and set 
// them to their default state
json::JSON FileManager::loadNewFile()
{
	try
	{
		std::ifstream inputStream("../Assets/SaveData/newGameData.game.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON gameData = json::JSON::Load(str);

		return gameData;
	}
	catch (...)
	{
		std::cout << "Error loading json file. Load aborted." << std::endl;
	}
	json::JSON emptyData;
	return emptyData;
}

// Loads the save data for the game. Used to update all gameobjects to reflect the state saved in the save file.
json::JSON FileManager::loadSaveFile()
{
	try
	{
		std::ifstream inputStream("../Assets/SaveData/gameSaveData.json");
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON gameData = json::JSON::Load(str);

		return gameData;
	}
	catch(...)
	{
		std::cout << "Error loading json file. Load aborted." << std::endl;
	}

	json::JSON emptyData;
	return emptyData;
}

