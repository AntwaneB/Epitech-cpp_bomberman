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
	_actions[BOMB_EXPLODED] = &Character::bombExploded;

	_attributes = g_settings["entities"]["character"];

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

void
Character::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	_bombs.erase(std::find(_bombs.begin(), _bombs.end(), bomb));
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
	(void)action; // We have to make the character to actually move

	_prevPosition = _position;

	this->notify(this, CHARACTER_MOVED);
}

void
Character::dropBomb()
{
	Bomb* bomb = new Bomb(); // We have to set it's position and the character it's related to

	_bombs.push_back(bomb);
	bomb->addObserver(this);

	this->notify(bomb, BOMB_DROPPED);
}
