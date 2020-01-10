#pragma once

#ifndef IINTERACTABLE_H
#define IINTERACTABLE_H

// Abstract class interface, which is inherited from by classes that can react to player interaction,
// so if an object can be searched or attacked by the player, for example, it should implement this class
class IInteractable
{
public:
	IInteractable() = default;
	virtual ~IInteractable() = default;

	virtual void onAttack() = 0;
	virtual void onPickUp() = 0;
	virtual void onSearch() = 0;
	virtual void onHide() = 0;
};

#endif // !IINTERACTABLE_H



