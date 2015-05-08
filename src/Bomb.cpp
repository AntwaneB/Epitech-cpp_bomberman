/*
 * File:   Bomb.cpp
 * Author: buchse_a
 *
 * Created on May 7, 2015, 12:15 AM
 */

#include "global.hh"
#include "Bomb.hh"

Bomb::Bomb(Position const & position, size_t range, double duration, const Character* owner)
	: Item(position), _range(range), _duration(duration), _owner(owner)
{
	_attributes = g_settings["entities"]["bomb"];
}

Bomb::~Bomb()
{
}

bool
Bomb::hasHit(Position const & position) const
{
	return (std::find(_hitbox.begin(), _hitbox.end(), position) != _hitbox.end());
}

void
Bomb::setHitbox(std::vector<Position> const & hitbox)
{
	_hitbox = hitbox;
}
