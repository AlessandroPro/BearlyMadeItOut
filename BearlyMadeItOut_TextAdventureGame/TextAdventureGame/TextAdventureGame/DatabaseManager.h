#pragma once

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Player.h"
#include <iostream>
#include "sqlite3.h"

// Singleton that onnects to and updates the stats database for this game
class DatabaseManager
{
public:
	static DatabaseManager& Instance();
	void destroy();
	void logPlayerStats(const PlayerActionStats& stats);

private:

	explicit DatabaseManager() = default;
	~DatabaseManager() = default;

	static DatabaseManager* instance;

	inline explicit DatabaseManager(DatabaseManager const&) {};
	inline DatabaseManager& operator=(DatabaseManager const&) { return *this; };
	void checkBindResult(int result, sqlite3* db);
};

#endif // !DATABASEMANAGER_H



