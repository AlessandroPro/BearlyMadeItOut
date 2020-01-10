#pragma once

#ifndef CLOTHING_H
#define CLOTHING_H

#include "Item.h"
#include "json.hpp"

// An item that represents the key clothing items required by the player to win the game
class Clothing : public Item
{
public:
	virtual void onPickUp() override;
	virtual void onDrop() override;
	static GameObject* create(json::JSON& gameObjectNode, bool newGame);
	static void load(json::JSON& gameObjectNode);
	json::JSON save(std::string& locationName, std::string& owner);
};

#endif // !CLOTHING_H



