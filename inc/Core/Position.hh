/*
 * File:   Position.hpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#ifndef POSITION_HPP
#define	POSITION_HPP

#include <iostream>
#include "Config.hh"

enum Direction { UP, DOWN, LEFT, RIGHT };

class Position
{
public:
	Position();
	Position(double x, double y, double z = 0);
	Position(const Position& orig);
	Position& operator=(const Position& orig);
	virtual ~Position();

	bool	operator==(Position const & o) const;
	bool	operator!=(Position const & o) const;
	bool	operator<(Position const & o) const;

	void	setZ(double z);
	void	incZ(double inc = 1);
	void	decZ(double dec = 1);
	double	z() const;
	void	setY(double y);
	void	incY(double inc = 1);
	void	decY(double dec = 1);
	double	y() const;
	void	setX(double x);
	void	incX(double inc = 1);
	void	decX(double dec = 1);
	double	x() const;
	bool	isSet() const;
	bool	outOfBounds(double maxX, double maxY) const;

	void	toConfig(Config &) const;

private:
	double	_x;
	double	_y;
	double	_z;
	bool		_isSet;
};

std::ostream& operator<<(std::ostream&, const Position &);
Position operator+(const Position &, const Position &);
void operator+=(Position &, const Position &);
Position operator-(const Position &, const Position &);
void operator-=(Position &, const Position &);

#endif	/* POSITION_HPP */

