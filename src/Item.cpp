/*
 * File:   Item.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:30 PM
 */

#include "Item.hh"

Item::Item(Position const & position)
	: _position(position), _prevPosition(position), _clockInit(false)
{
}

Item::~Item()
{
}

Position
Item::position() const
{
	return (_position);
}

Position
Item::prevPosition() const
{
	return (_prevPosition);
}

/*
void
Item::toConfig(Config & cfg) const
{
	_position.toConfig(cfg["position"]);
	_prevPosition.toConfig(cfg["prevPosition"]);
	cfg["clockInit"] = _clockInit;
	cfg["spawnTime"] = _spawnTime;
}
*/