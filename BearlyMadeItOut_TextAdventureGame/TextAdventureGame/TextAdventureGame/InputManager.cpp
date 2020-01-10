#include "InputManager.h"
#include <algorithm>
#include <iostream>
#include <windows.h>

InputManager* InputManager::instance = nullptr;


InputManager& InputManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new InputManager;
	}
	return *instance;
}

void InputManager::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// Returns string as an uppercase string
std::string InputManager::toUpper(const std::string string)
{
	std::string stringUpper = string;
	std::for_each(stringUpper.begin(), stringUpper.end(), [](char& c)
		{
			c = ::toupper(c);
		});

	return stringUpper;
}

// Parses player input and returns it as a command, argument Spair:
// Command: Is the fist word
// Argument: Is everything else
std::pair<std::string, std::string> InputManager::getCommand()
{
	std::string input;
	std::string command;
	std::string argument;
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << ">> ";
	std::getline(std::cin, input);
	
	command = input.substr(0, input.find(' '));

	if (command.size() + 1 < input.size())
	{
		argument = input.substr(command.size() + 1);
	}

	SetConsoleTextAttribute(hConsole, 11);

	return std::pair<std::string, std::string>(toUpper(command), argument);
}
