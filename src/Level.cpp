/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#include "Level.hpp"

Level::Level(size_t width, size_t height, size_t charactersCount)
	: _map(width, height)
{
	for (size_t i = 0; i < charactersCount; i++)
	{
		
	}
}

Level::~Level()
{
}

void
Level::onNotify(Subject * entity, Event event)
{
	(void)entity;
	(void)event;
}
