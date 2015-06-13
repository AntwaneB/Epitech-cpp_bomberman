/*
 * File:   Position.hpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#ifndef POSITION_HPP
#define	POSITION_HPP

#include <iostream>
#include "Exception.hpp"
#include "Config.hh"

enum Direction { UP, DOWN, LEFT, RIGHT };

template <typename T = int>
class Position
{
	friend class	Save;

public:
	Position();
	Position(T x, T y, T z = 0);
	Position(const Position& orig);
	Position(Config::Param &);
	Position& operator=(const Position& orig);
	virtual ~Position();

	bool	operator==(Position const & o) const;
	bool	operator!=(Position const & o) const;
	bool	operator<(Position const & o) const;

	void	setZ(T z);
	void	incZ(T inc = 1);
	void	decZ(T dec = 1);
	T	z() const;
	void	setY(T y);
	void	incY(T inc = 1);
	void	decY(T dec = 1);
	T	y() const;
	void	setX(T x);
	void	incX(T inc = 1);
	void	decX(T dec = 1);
	T	x() const;
	bool	isSet() const;
	bool	outOfBounds(T maxX, T maxY) const;

	Position<int> asInt() const;
	Position<double> asDouble() const;
	operator Position<int>() const;
	operator Position<double>() const;

private:
	T	_x;
	T	_y;
	T	_z;
	bool		_isSet;
};

/*
std::ostream& operator<<(std::ostream&, const Position &);
Position operator+(const Position &, const Position &);
void operator+=(Position &, const Position &);
Position operator-(const Position &, const Position &);
void operator-=(Position &, const Position &);
*/

template <typename T>
Position<T>::Position(T x, T y, T z)
	: _x(x), _y(y), _z(z), _isSet(true)
{
}

template <typename T>
Position<T>::Position()
	: _x(0), _y(0), _z(0), _isSet(false)
{
}

template <typename T>
Position<T>::Position(const Position& orig)
	: _x(orig._x), _y(orig._y), _z(orig._z), _isSet(orig._isSet)
{
}

template <typename T>
Position<T>::Position(Config::Param & cfg)
	: _x(cfg["x"]), _y(cfg["y"]), _z(cfg["z"]), _isSet(cfg["isSet"])
{
}

template <typename T>
Position<T>&
Position<T>::operator=(const Position& orig)
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

template <typename T>
Position<T>::~Position()
{
}

template <typename T>
bool
Position<T>::operator<(const Position & o) const
{
	return ((_y < o._y) || (_y == o._y && _x < o._x));
}

template <typename T>
bool
Position<T>::operator!=(const Position & o) const
{
	return ((_x != o._x) || (_y != o._y) || (_z != o._z));
}

template <typename T>
void
Position<T>::setZ(T z)
{
	this->_z = z;
	this->_isSet = true;
}

template <typename T>
void
Position<T>::incZ(T inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_z += inc;
}

template <typename T>
void
Position<T>::decZ(T dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_z -= dec;
}

template <typename T>
T
Position<T>::z() const
{
	if (!_isSet)
		throw PositionException("Getting unset position.");
	return _z;
}

template <typename T>
void
Position<T>::setY(T y)
{
	this->_y = y;
	this->_isSet = true;
}

template <typename T>
void
Position<T>::incY(T inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_y += inc;
}

template <typename T>
void
Position<T>::decY(T dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_y -= dec;
}

template <typename T>
T
Position<T>::y() const
{
	if (!_isSet)
		return (0);
	//throw PositionException("Getting unset position.");
	return _y;
}

template <typename T>
void
Position<T>::setX(T x)
{
	this->_x = x;
	this->_isSet = true;
}

template <typename T>
void
Position<T>::incX(T inc)
{
	if (!_isSet)
		throw PositionException("Increasing unset position.");
	this->_x += inc;
}

template <typename T>
void
Position<T>::decX(T dec)
{
	if (!_isSet)
		throw PositionException("Decreasing unset position.");
	this->_x -= dec;
}

template <typename T>
T
Position<T>::x() const
{
	if (!_isSet)
		return (0);
		//throw PositionException("Getting unset position.");
	return _x;
}

template <typename T>
bool
Position<T>::isSet() const
{
	return (_isSet);
}

template <typename T>
bool
Position<T>::operator==(Position const & o) const
{
	return (o._x == _x && o._y == _y && o._z == _z);
}

template <typename T>
bool
Position<T>::outOfBounds(T maxX, T maxY) const
{
	return (_x <= 0 || _x >= maxX || _y <= 0 || _y >= maxY);
}

template <typename T>
Position<int>
Position<T>::asInt() const
{
	return (Position<int>(static_cast<int>(_x), static_cast<int>(_y), static_cast<int>(_z)));
}
template <typename T>
Position<T>::operator Position<int>() const
{
	return (Position<int>(static_cast<int>(_x), static_cast<int>(_y), static_cast<int>(_z)));
}

template <typename T>
Position<double>
Position<T>::asDouble() const
{
	return (Position<double>(static_cast<double>(_x), static_cast<double>(_y), static_cast<double>(_z)));
}
template <typename T>
Position<T>::operator Position<double>() const
{
	return (Position<double>(static_cast<double>(_x), static_cast<double>(_y), static_cast<double>(_z)));
}

template <typename T>
std::ostream&
operator<<(std::ostream& os, const Position<T> & position)
{
	os << "[" << position.x() << "/" << position.y() << "/" << position.z() << "]";

	return (os);
}

template <typename T>
Position<T>
operator+(const Position<T> & pos1, const Position<T> & pos2)
{
	return (Position<T>(pos1.x() + pos2.x(), pos1.y() + pos2.y(), pos1.z() + pos2.z()));
}

template <typename T, typename U>
void
operator+=(Position<T> & pos1, const Position<U> & pos2)
{
	pos1.incX(pos2.x());
	pos1.incY(pos2.y());
	pos1.incZ(pos2.z());
}

template <typename T>
Position<T>
operator-(const Position<T> & pos1, const Position<T> & pos2)
{
	return (Position<T>(pos1.x() - pos2.x(), pos1.y() - pos2.y(), pos1.z() - pos2.z()));
}

template <typename T, typename U>
void
operator-=(Position<T> & pos1, const Position<U> & pos2)
{
	pos1.decX(pos2.x());
	pos1.decY(pos2.y());
	pos1.decZ(pos2.z());
}


#endif	/* POSITION_HPP */

