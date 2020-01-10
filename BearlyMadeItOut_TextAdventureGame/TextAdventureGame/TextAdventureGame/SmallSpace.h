#pragma once

#ifndef SMALLSPACE_H
#define SMALLSPACE_H

#include "GameObject.h"
#include "IInteractable.h"
#include <list>
#include "Guard.h"
#include "json.hpp"

// Represents a small space (like a foutnain or a trashcan) that can exist within a location.
// Can be used store items and hide unconcious guards
class SmallSpace : public GameObject, public IInteractable
{
private:

	std::list<Item*> items;
	Guard* hiddenGuard = nullptr;

public:

	SmallSpace() = default;
	virtual ~SmallSpace();
	void dropAllItems();
	void hideGuard(Guard* guard);
	void addItem(Item* item);
	Guard* getGuard();
	const std::list<Item*>& getItems();

	virtual void onAttack() override;
	virtual void onPickUp() override;
	virtual void onSearch() override;
	virtual void onHide() override;

	static GameObject* create(json::JSON& gameObjectNode, bool newGame);
};

#endif // !SMALLSPACE_H



