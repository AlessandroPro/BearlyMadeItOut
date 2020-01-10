#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>

// Singleton that handles the retriveal and parsing of player input and string manipulation
class InputManager
{
public:

	static InputManager& Instance();
	void destroy();

	std::string toUpper(const std::string stringValue);
	std::pair<std::string, std::string> getCommand();

private:

	explicit InputManager() = default;
	~InputManager() = default;

	static InputManager* instance;

	inline explicit InputManager(InputManager const&) {};
	inline InputManager& operator=(InputManager const&) { return *this; };
};

#endif // !INPUTMANAGER_H