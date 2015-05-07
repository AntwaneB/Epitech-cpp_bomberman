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
	: _nth(nth), _position(x, y, z)
{
	_actions[CLOCK_TICK] = &Character::tick;

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

	(void)clock;
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
Character::move()
{
	_prevPosition = _position;

	this->notify(this, CHARACTER_MOVED);
}
