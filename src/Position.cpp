#include "Position.hpp"

Position::Position(int x, int y, int z): _x(x), _y(y), _z(z)
{

}

Position::~Position()
{

}

int Position::getX() const
{
	return (this->_x);
}

int Position::getY() const
{
	return (this->_y);
}

int Position::getZ() const
{
	return (this->_z);
}