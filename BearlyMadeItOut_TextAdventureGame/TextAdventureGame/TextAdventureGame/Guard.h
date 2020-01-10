#pragma once

#ifndef GUARD_H
#define GUARD_H

#include "GameObject.h"
#include "IInteractable.h"
#include "Item.h"
#include "json.hpp"

// The enemy within this game, can be placed in different location and tranquilzie the player 
class Guard : public GameObject, public IInteractable
{
private:
	bool isConscious = true;
	Item* item = nullptr;

public:

	Guard();
	virtual ~Guard();

	virtual void update() override;
	void onAlert();
	void dropItem();
	void setItem(Item* guardItem);
	Item* getItem();
	bool checkIsConscious();
	void setConscious(bool conscious);
	void printStatus();


	virtual void onAttack() override;
	virtual void onPickUp() override;
	virtual void onSearch() override;
	virtual void onHide() override;

	static GameObject* create(json::JSON& gameObjectNode, bool newGame);
	static void load(json::JSON& gameObjectNode);
	json::JSON save(std::string& locationName, bool hidden);
};

#endif




