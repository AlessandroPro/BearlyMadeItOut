#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager& DatabaseManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new DatabaseManager();
	}
	return *instance;
}

void DatabaseManager::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void DatabaseManager::logPlayerStats(const PlayerActionStats& stats)
{
	sqlite3* db = nullptr;
	char* zErrMsg = 0;
	int rc = 0;

	rc = sqlite3_open("../Assets/Database/TextBasedGameAnalytics.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}

	sqlite3_stmt* stmt = nullptr;
	int result = 0;

	// Create statment
	result = sqlite3_prepare_v2(db, "INSERT INTO player_stats(num_travel, num_attack, num_pickup, num_drop, num_search, num_hide, num_respawn) values (?, ?, ?, ?, ?, ?, ?)", -1, &stmt, 0);
	if (result != SQLITE_OK)
	{
		std::cout << sqlite3_errmsg(db);
		printf("\nCould not prepare statement.");
	}

	// Bind parameter count
	sqlite3_bind_parameter_count(stmt);

	result = sqlite3_bind_int(stmt, 1, stats.numTravel);
	checkBindResult(result, db);

	result = sqlite3_bind_int(stmt, 2, stats.numAttack);
	checkBindResult(result, db);

	result = sqlite3_bind_int(stmt, 3, stats.numPickup);
	checkBindResult(result, db);

	result = sqlite3_bind_int(stmt, 4, stats.numDrop);
	checkBindResult(result, db);

	result = sqlite3_bind_int(stmt, 5, stats.numSearch);
	checkBindResult(result, db);

	result = sqlite3_bind_int(stmt, 6, stats.numHide);
	checkBindResult(result, db);

	result = sqlite3_bind_int(stmt, 7, stats.numRespawn);
	checkBindResult(result, db);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
	{
		std::cout << sqlite3_errmsg(db);
	}
}

// Ensure the sql statment executed without errors
void DatabaseManager::checkBindResult(int result, sqlite3* db)
{
	if (result != SQLITE_OK)
	{
		std::cout << sqlite3_errmsg(db);
	}
}

