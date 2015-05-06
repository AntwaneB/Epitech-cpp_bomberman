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
	size_t blocksPerLine = _map.width() > _map.height() ? ceil(sqrt(_charactersCount)) : floor(sqrt(_charactersCount));
	size_t lines = _map.width() > _map.height() ? floor(sqrt(_charactersCount)) : ceil(sqrt(_charactersCount));

	size_t blockWidth = _map.width() / blocksPerLine;
	size_t blockHeight = _map.height() / lines;

	size_t nth = _characters.size();

	size_t charX = (nth % blocksPerLine) * blockWidth + blockWidth / 2;
	size_t charY = (nth / blocksPerLine) * blockHeight + blockHeight / 2;

	/*
	int charX = (_map.width() / (charsPerLine - 1)) * (nth % charsPerLine);
	int charY = (_map.height() / (charsPerCol - 1)) * (nth / charsPerLine);

	std::cout << "(" << _map.width() << " / " << charsPerLine - 1 << ") * (" << nth << " % " << charsPerLine << ") = " << charX << std::endl;
	std::cout << "(" << _map.height() << " / " << charsPerCol - 1 << ") * (" << nth << " / " << charsPerLine << ") = " << charY << std::endl;
	*/

	Character*	character = new Character(nth + 1, charX, charY);
	character->addObserver(this);

	_characters[Position(charX, charY)].push_back(character);

	return (character);
}
