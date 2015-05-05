#include "Position.hpp"

Position::Position(double x, double y, double z): _x(x), _y(y), _z(z)
{

}

Position::~Position()
{

}

double Position::getX() const
{
	return (this->_x);
}

double Position::getY() const
{
	return (this->_y);
}

double Position::getZ() const
{
	return (this->_z);
}