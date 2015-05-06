/*
 * File:   Character.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#include "Character.hpp"

Character::Character(size_t nth, size_t x, size_t y, size_t z)
	: _nth(nth), _position(x, y, z)
{
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

