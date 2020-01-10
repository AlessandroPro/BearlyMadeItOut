#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "GameObject.h"
#include "IInteractable.h"
#include "ItemCheck.h"
#include "json.hpp"

// An item in the game
class Item : public GameObject, public IInteractable
{
protected:
	bool isAccessible = true;
  	ItemCheck itemCheck;
	std::string inaccessibleDesc;
	std::string inaccessMessage;
	std::string accessMessage;

public:
	Item();
	virtual ~Item() = default;
	virtual void update() override;
	virtual void onDrop();
	void setAccessible(bool accessible);

	virtual void onAttack() override;
	virtual void onPickUp() override;
	virtual void onSearch() override;
	virtual void onHide() override;

	static GameObject* create(json::JSON& gameObjectNode, bool newGame);
	static void load(json::JSON& gameObjectNode);
	json::JSON save(std::string& locationName, std::string& owner);

};

#endif // !ITEM_H



