#pragma once

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "FileManager.h"
#include "InputManager.h"
#include "GameManager.h"

// Singleton that spawns all systems for the game
class GameEngine
{
public:
	static GameEngine& Instance();
	void startUp();
	void destroy();

private:
	static GameEngine* instance;

	explicit GameEngine() = default;
	~GameEngine();

	inline explicit GameEngine(GameEngine const&) {};
	inline GameEngine& operator=(GameEngine const&) { return *this; };
};

#endif // !GAMEENGINE_H
