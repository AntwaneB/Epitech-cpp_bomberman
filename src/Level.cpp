/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#include "Level.hpp"

Level::Level(size_t width, size_t height, size_t charactersCount)
	: _map(width, height), _charactersCount(charactersCount)
{
	for (size_t i = 0; i < charactersCount; i++)
	{
		_map.pushCharacter(this->pushCharacter());
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

void
Level::run()
{
	this->notify(this, LEVEL_STARTED);
}

Character*
Level::pushCharacter()
{
	size_t charsPerLine = ceil(sqrt(_charactersCount));
	size_t charsPerCol = floor(sqrt(_charactersCount));

	size_t nth = _characters.size() + 0;

	size_t charX = _map.width() / charsPerLine * (nth % charsPerLine - 1);
	size_t charY = _map.height() / charsPerCol * (nth / charsPerLine);

	Character*	character = new Character(nth, charX, charY);

	_characters[Position(charX, charY)].push_back(character);

	this->notify(character, CHARACTER_SPAWNED);

	return (character);
}