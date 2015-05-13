/*
 * File:   Position.hpp
 * Author: buchse_a
 *
 * Created on March 9, 2015, 11:31 AM
 */

#ifndef POSITION_HPP
#define	POSITION_HPP

#include "Config.hpp"
#include <iostream>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Position
{
public:
	Position();
	Position(int x, int y, int z = 0);
	Position(const Position& orig);
	Position& operator=(const Position& orig);
	virtual ~Position();

	bool	operator==(Position const & o) const;
	bool	operator<(Position const & o) const;

	Position&	operator+=(Position const & o);
	Position&	operator-=(Position const & o);

	void	setZ(int z);
	void	incZ(int inc = 1);
	void	decZ(int dec = 1);
	int	z() const;
	void	setY(int y);
	void	incY(int inc = 1);
	void	decY(int dec = 1);
	int	y() const;
	void	setX(int x);
	void	incX(int inc = 1);
	void	decX(int dec = 1);
	int	x() const;
	bool	isSet() const;

	void	toConfig(Config &) const;

private:
	int	_x;
	int	_y;
	int	_z;
	bool	_isSet;
};

std::ostream& operator<<(std::ostream&, const Position &);

#endif	/* POSITION_HPP */

