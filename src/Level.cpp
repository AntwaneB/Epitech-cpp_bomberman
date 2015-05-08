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
	_actions[CLOCK_TICK] = &Level::tick;
	_actions[CHARACTER_MOVED] = &Level::characterMoved;
	_actions[CHARACTER_DIED] = &Level::characterDied;
	_actions[ITEM_DROPPED] = &Level::itemDropped;
	_actions[ITEM_MOVED] = &Level::itemMoved;
	_actions[BOMB_EXPLODED] = &Level::bombExploded;

	_clock.addObserver(this);

	for (size_t i = 0; i < charactersCount; i++)
	{
		_map.pushCharacter(this->pushCharacter());
	}
}

Level::~Level()
{
}

Clock&
Level::clock()
{
	return (_clock);
}

void
Level::run()
{
	this->notify(this, LEVEL_STARTED);

	_clock.restart();
	_clock.resetSec();
	_clock.run();
}

void
Level::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);
	if (clock == &_clock)
	{


		this->notify(this, LEVEL_UPDATED);
	}
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

	_clock.addObserver(character);

	return (character);
}

void
Level::characterMoved(Subject* entity)
{
	Character* character = safe_cast<Character*>(entity);

	_characters[character->prevPosition()].erase(std::find(_characters[character->prevPosition()].begin(), _characters[character->prevPosition()].end(), character));
	_characters[character->position()].push_back(character);
}

void
Level::characterDied(Subject* entity)
{
	Character* character = safe_cast<Character*>(entity);

	_characters[character->prevPosition()].erase(std::find(_characters[character->prevPosition()].begin(), _characters[character->prevPosition()].end(), character));
	_clock.removeObserver(character);
}

void
Level::itemDropped(Subject* entity)
{
	Item* item = safe_cast<Item*>(entity);

	_clock.addObserver(item);
}

void
Level::itemMoved(Subject* entity)
{
	Item* item = safe_cast<Item*>(entity);

	_items[item->prevPosition()].erase(std::find(_items[item->prevPosition()].begin(), _items[item->prevPosition()].end(), item));
	_items[item->position()].push_back(item);
}

void
Level::bombDropped(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	_bombs[bomb->position()].push_back(bomb);
	_clock.addObserver(bomb);
}

void
Level::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	// We have to set the hitbox for the bomb

	_items[bomb->position()].erase(std::find(_items[bomb->position()].begin(), _items[bomb->position()].end(), bomb));
	_clock.removeObserver(bomb);

	this->notify(bomb, LEVEL_BOMB_EXPLODED);
}
