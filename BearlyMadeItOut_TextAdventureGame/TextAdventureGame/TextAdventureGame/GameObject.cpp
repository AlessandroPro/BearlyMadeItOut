#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include "InputManager.h"


std::string GameObject::getName()
{
	return name;
}

void GameObject::setName(const std::string& objectName)
{
	name = objectName;
}

std::string GameObject::nameAsUpper()
{
	return InputManager::Instance().toUpper(name);
}


void GameObject::update()
{
}

void GameObject::initialize()
{
}

void GameObject::display()
{
	std::cout << "GameObject: " << name << std::endl;
}

