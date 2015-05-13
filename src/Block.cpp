/*
 * File:   Block.cpp
 * Author: buchse_a
 *
 * Created on May 11, 2015, 11:27 AM
 */

#include "Block.hh"

Block::Block(Position const & position, std::string const & type)
	: _position(position), _type(type), _elapsedTime(0)
{
	_actions[CLOCK_TICK] = &Block::tick;
	_actions[LEVEL_BOMB_EXPLODED] = &Block::bombExploded;

	_attributes = g_settings["entities"][_type];
}

Block::~Block()
{
}

Position
Block::position() const
{
	return (_position);
}

bool
Block::destructible() const
{
	return (_attributes["destructible"]);
}

bool
Block::visible() const
{
	return (_attributes["visible"]);
}

bool
Block::solid() const
{
	return (_attributes["collision"]);
}

void
Block::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	if (destructible() && bomb->hasHit(_position))
	{ // The block got hit by the bomb and is destructible
		this->notify(this, BLOCK_DESTROYED);
	}
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
	}
}
