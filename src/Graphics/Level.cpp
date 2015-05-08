/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 8, 2015, 2:05 PM
 */

#include "Graphics/Level.hh"

Graphics::Level::Level(::Level const * level)
	: _level(level)
{

}

Graphics::Level::~Level()
{
}

bool
Graphics::Level::initialize()
{
	return (true);
}

bool
Graphics::Level::update()
{
	return (true);
}

void
Graphics::Level::draw()
{

}
