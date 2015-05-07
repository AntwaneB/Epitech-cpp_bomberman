/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#include "Exception.hpp"
#include "Level.hpp"

Level::Level(size_t width, size_t height, size_t charactersCount)
	: _map(width, height), _charactersCount(charactersCount)
{
	_actions[CHARACTER_MOVED] = &Level::characterMoved;
	_actions[CHARACTER_DIED] = &Level::characterDied;
	_actions[ITEM_DROPPED] = &Level::itemDropped;
	_actions[ITEM_MOVED] = &Level::itemMoved;
	_actions[BOMB_EXPLODED] = &Level::bombExploded;

	for (size_t i = 0; i < charactersCount; i++)
	{
		_map.pushCharacter(this->pushCharacter());
	}
}

Level::~Level()
{
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

	Character*	character = new Character(nth + 1, charX, charY);
	character->addObserver(this);

	_characters[Position(charX, charY)].push_back(character);

	return (character);
}

void
Level::characterMoved(Subject* entity)
{
	if (dynamic_cast<Character*>(entity))
	{
		Character* character = dynamic_cast<Character*>(entity);

		_characters[character->prevPosition()].erase(std::find(_characters[character->prevPosition()].begin(), _characters[character->prevPosition()].end(), (character)));
		_characters[character->position()].push_back(character);
	}
	else
		throw EventException("Event thrown on not-matching entity");
}

void
Level::characterDied(Subject* entity)
{
	if (dynamic_cast<Character*>(entity))
	{
		Character* character = dynamic_cast<Character*>(entity);

		_characters[character->prevPosition()].erase(std::find(_characters[character->prevPosition()].begin(), _characters[character->prevPosition()].end(), (character)));
	}
	else
		throw EventException("Event thrown on not-matching entity");
}

void
Level::itemDropped(Subject* entity)
{
	if (dynamic_cast<Item*>(entity))
	{
		Item* item = dynamic_cast<Item*>(entity);

		(void)item;
	}
	else
		throw EventException("Event thrown on not-matching entity");
}

void
Level::itemMoved(Subject* entity)
{
	if (dynamic_cast<Item*>(entity))
	{
		Item* item = dynamic_cast<Item*>(entity);

		_items[item->prevPosition()].erase(std::find(_items[item->prevPosition()].begin(), _items[item->prevPosition()].end(), (item)));
		_items[item->position()].push_back(item);
	}
	else
		throw EventException("Event thrown on not-matching entity");
}

void
Level::bombExploded(Subject* entity)
{
	if (dynamic_cast<Bomb*>(entity))
	{
		Bomb* bomb = dynamic_cast<Bomb*>(entity);

		(void)bomb;
	}
	else
		throw EventException("Event thrown on not-matching entity");
}
