/*
 * File:   Item.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:30 PM
 */

#include "Exception.hpp"
#include "Core/Item.hh"
#include "Core/RangeIncreaser.hh"
#include "Core/SpeedIncreaser.hh"
#include "Core/BombAmountIncreaser.hh"

Item::Item(Position<> const & position, Type type)
	: _position(position), _prevPosition(position), _type(type), _clockInit(false), _spawnTime(0)
{
}

Item::Item(Config::Param cfg)
	: _position(cfg["position"]), _prevPosition(cfg["prevPosition"]), _type(), _clockInit(cfg["clockInit"]), _spawnTime(cfg["spawnTime"]), _type(cfg["type"])
{
}

Item::~Item()
{
}

Item::Type
Item::type() const
{
	return (_type);
}

Position<>
Item::position() const
{
	return (_position);
}

Position<>
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