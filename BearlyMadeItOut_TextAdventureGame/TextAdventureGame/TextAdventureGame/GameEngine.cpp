#include "GameEngine.h"
#include "DatabaseManager.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::~GameEngine()
{
	FileManager::Instance().destroy();
	InputManager::Instance().destroy();
	GameManager::Instance().destroy();
	DatabaseManager::Instance().destroy();
}

GameEngine& GameEngine::Instance()
{
	if (instance == nullptr)
	{
		instance = new GameEngine();
	}
	return *instance;
}

// Start the game loop
void GameEngine::startUp()
{
	GameManager::Instance().initialize();
	GameManager::Instance().playGame();
}

void GameEngine::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
