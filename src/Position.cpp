/*
 * File:   Position.cpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#include "Exception.hpp"
#include "Core/Position.hpp"

Position::Position(int x, int y, int z)
	: _x(x), _y(y), _z(z), _isSet(true)
{
}

Position::Position()
	: _x(0), _y(0), _z(0), _isSet(false)
{
}

Position::Position(const Position& orig)
	: _x(orig._x), _y(orig._y), _z(orig._z), _isSet(orig._isSet)
{
}

Position&
Position::operator=(const Position& orig)
{
	if (this != &orig)
	{
		_x = orig._x;
		_y = orig._y;
		_z = orig._z;
		_isSet = orig._isSet;
	}
	return (*this);
}

Position::~Position()
{
}

bool
Position::operator<(const Position & o) const
{
	return ((_y < o._y) || (_y == o._y && _x < o._x));
}

bool
Position::operator!=(const Position & o) const
{
	return ((_x != o._x) || (_y != o._y) || (_z != o._z));
}

void
Position::setZ(int z)
{
	this->_z = z;
	this->_isSet = true;
}

void
Position::incZ(int inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_z += inc;
}

void
Position::decZ(int dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_z -= dec;
}

int
Position::z() const
{
	if (!_isSet)
		throw PositionException("Getting unset position.");
	return _z;
}

void
Position::setY(int y)
{
	this->_y = y;
	this->_isSet = true;
}

void
Position::incY(int inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_y += inc;
}

void
Position::decY(int dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_y -= dec;
}

int
Position::y() const
{
	if (!_isSet)
		return (0);
	//throw PositionException("Getting unset position.");
	return _y;
}

void
Position::setX(int x)
{
	this->_x = x;
	this->_isSet = true;
}

void
Position::incX(int inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_x += inc;
}

void
Position::decX(int dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_x -= dec;
}

int
Position::x() const
{
	if (!_isSet)
		return (0);
		//throw PositionException("Getting unset position.");
	return _x;
}

bool
Position::isSet() const
{
	return (_isSet);
}

bool
Position::operator==(Position const & o) const
{
	return (o._x == _x && o._y == _y && o._z == _z);
}

bool
Position::outOfBounds(int maxX, int maxY) const
{
	return (_x <= 0 || _x >= maxX || _y <= 0 || _y >= maxY);
}

std::ostream&
operator<<(std::ostream& os, const Position & position)
{
	os << "[" << position.x() << "/" << position.y() << "/" << position.z() << "]";

	return (os);
}

void
Position::toConfig(Config & cfg) const
{
	cfg["x"] = _x;
	cfg["y"] = _y;
	cfg["z"] = _z;
	cfg["isSet"] = _isSet;
}

Position operator+(const Position & pos1, const Position & pos2)
{
	return (Position(pos1.x() + pos2.x(), pos1.y() + pos2.y(), pos1.z() + pos2.z()));
}

void operator+=(Position & pos1, const Position & pos2)
{
	pos1.incX(pos2.x());
	pos1.incY(pos2.y());
	pos1.incZ(pos2.z());
}

Position operator-(const Position & pos1, const Position & pos2)
{
	return (Position(pos1.x() - pos2.x(), pos1.y() - pos2.y(), pos1.z() - pos2.z()));
}

void operator-=(Position & pos1, const Position & pos2)
{
	pos1.decX(pos2.x());
	pos1.decY(pos2.y());
	pos1.decZ(pos2.z());
}
