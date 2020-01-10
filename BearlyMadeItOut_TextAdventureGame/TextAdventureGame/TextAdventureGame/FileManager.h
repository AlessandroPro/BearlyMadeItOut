#pragma once

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "json.hpp"

// Singleton that manages the reading and writing of files for the game
class FileManager
{
public:
	static FileManager& Instance();
	void destroy();

	void saveFile(const json::JSON& document);
	json::JSON loadNewFile();
	json::JSON loadSaveFile();

private:

	explicit FileManager() = default;
	~FileManager() = default;

	static FileManager* instance;

	inline explicit FileManager(FileManager const&) {};
	inline FileManager& operator=(FileManager const&) { return *this; };
};

#endif // !FILEMANAGER_H



