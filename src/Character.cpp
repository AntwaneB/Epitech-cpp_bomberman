/*
 * File:   Character.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#include <iostream>
#include "global.hh"
#include "Character.hpp"
#include "Exception.hpp"
#include "Clock.hpp"

Character::Character(size_t nth, size_t x, size_t y, size_t z)
	: _nth(nth), _position(x, y, z), _elapsedTime(-1)
{
	_actions[CLOCK_TICK] = &Character::tick;

	_attributes = g_settings["entities"]["character"];

	if (_nth == 6)
	{
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::DROP_BOMB);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::MOVE_UP);
		_queuedActions.push(Character::DROP_BOMB);
		_queuedActions.push(Character::DROP_BOMB);
		_queuedActions.push(Character::MOVE_UP);
	}

	this->notify(this, CHARACTER_SPAWNED);
}

Character::~Character()
{
}

void
Character::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);

	if (_elapsedTime == -1)
		_elapsedTime = clock->deciseconds();

	if (static_cast<int>(clock->deciseconds()) - _elapsedTime >= 1)
	{
		_elapsedTime++;

		if (_queuedActions.size() > 0
			&& (_queuedActions.front() == Character::MOVE_UP || _queuedActions.front() == Character::MOVE_DOWN
			 || _queuedActions.front() == Character::MOVE_LEFT || _queuedActions.front() == Character::MOVE_RIGHT)
			&& _attributes["can_move"] == true
			&& _attributes["speed"] != 0
			&& _elapsedTime % (1000 / static_cast<int>(_attributes["speed"])) == 0)
		{ // Triggering movement
			Character::Action movement = _queuedActions.front();
			_queuedActions.pop();

			this->move(movement);
		}

		if (_queuedActions.size() > 0 && _queuedActions.front() == Character::DROP_BOMB)
		{ // Dropping a bomb
			_queuedActions.pop();

			if (_attributes["bombs"]["available"] == true
				&& _bombs.size() < static_cast<size_t>(_attributes["bombs"]["max_amount"]))
			{
				this->dropBomb();
			}
		}

	}
}

Position
Character::position() const
{
	return (_position);
}

Position
Character::prevPosition() const
{
	return (_prevPosition);
}

void
Character::move(Character::Action action)
{
	(void)action;

	_prevPosition = _position;

	std::cout << "Character " << _nth << " is moving" << std::endl;
	this->notify(this, CHARACTER_MOVED);
}

void
Character::dropBomb()
{
	Bomb* bomb = new Bomb(); // We have to set it's position and the character it's related to

	_bombs.push_back(bomb);

	std::cout << "Character " << _nth << " is dropping a bomb" << std::endl;
	this->notify(bomb, ITEM_DROPPED);
}
