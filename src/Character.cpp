/*
 * File:   Character.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#include <iostream>
#include "Character.hpp"

Character::Character(size_t nth, size_t x, size_t y, size_t z)
	: _nth(nth), _position(x, y, z)
{
	std::cout << "Character spawned at " << _position << std::endl;

	this->notify(this, CHARACTER_SPAWNED);
}

Character::~Character()
{
}

void
Character::onNotify(Subject* entity, Event event)
{
	(void)entity;
	(void)event;
}

