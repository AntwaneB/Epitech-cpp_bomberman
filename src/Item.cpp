/*
 * File:   Item.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:30 PM
 */

#include "Item.hh"

Item::Item()
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