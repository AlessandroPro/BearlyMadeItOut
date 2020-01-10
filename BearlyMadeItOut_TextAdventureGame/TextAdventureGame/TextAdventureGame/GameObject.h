
#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "json.hpp"

// A generic game object 
class GameObject
{
protected:
	std::string name;

public:

	GameObject() = default;
	virtual ~GameObject() = default;

	std::string getName();
	void setName(const std::string& objectName);
	std::string nameAsUpper();
	virtual void update();
	virtual void initialize();
	virtual void display();
};

#endif // !GAMEOBJECT_H



