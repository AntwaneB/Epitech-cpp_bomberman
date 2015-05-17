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
	_actions[BOMB_DROPPED] = &Level::bombDropped;
	_actions[BOMB_EXPLODED] = &Level::bombExploded;

	_clock.addObserver(this);

	this->addObserver(&_map);
	_map.addObserver(this);

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

Map const &
Level::map() const
{
	return (_map);
}

size_t
Level::charactersCount() const
{
	return (_characters.size());
}

std::map<Position, std::list<Character*> > const &
Level::characters() const
{
	return (_characters);
}

std::map<Position, std::list<Bomb *> > const &
Level::bombs() const
{
	return _bombs;
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
	size_t blocksPerLine = _map.width() >= _map.height() ? ceil(sqrt(_charactersCount)) : floor(sqrt(_charactersCount));
	size_t lines = _map.width() > _map.height() ? floor(sqrt(_charactersCount)) : ceil(sqrt(_charactersCount));

	size_t blockWidth = _map.width() / blocksPerLine;
	size_t blockHeight = _map.height() / lines;

	size_t nth = _characters.size();

	size_t blockX = nth % blocksPerLine;
	size_t blockY = nth / blocksPerLine;

	size_t charX, charY;
	if (blockX == 0)
		charX = 1;
	else if (blockX == blocksPerLine - 1)
		charX = _map.width() - 2;
	else
		charX = blockX * blockWidth + blockWidth / 2;

	if (blockY == 0)
		charY = 1;
	else if (blockY == lines - 1)
		charY = _map.height() - 2;
	else
		charY = blockY * blockHeight + blockHeight / 2;

	Character*	character = new Character(nth + 1, charX, charY);
	character->addObserver(this);

	_characters[Position(charX, charY)].push_back(character);

	_clock.addObserver(character);
	this->addObserver(character);

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

	_characters[character->position()].erase(std::find(_characters[character->position()].begin(), _characters[character->position()].end(), character));
	_clock.removeObserver(character);
	this->removeObserver(character);
}

void
Level::itemDropped(Subject* entity)
{
	BonusItem* item = safe_cast<BonusItem*>(entity);

	_clock.addObserver(item);
	this->addObserver(item);
	item->addObserver(this);
}

void
Level::itemMoved(Subject* entity)
{
	BonusItem* item = safe_cast<BonusItem*>(entity);

	_items[item->prevPosition()].erase(std::find(_items[item->prevPosition()].begin(), _items[item->prevPosition()].end(), item));
	_items[item->position()].push_back(item);
}

void
Level::bombDropped(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	_bombs[bomb->position()].push_back(bomb);
	_clock.addObserver(bomb);
	this->addObserver(bomb);
	bomb->addObserver(this);
}

void
Level::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	/* Setting hitbox for the bomb */
	std::vector<Position> hitbox;
	size_t	range = bomb->range();

	Position explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.decY();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
	}
	explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.incY();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
	}
	explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.decX();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
	}
	explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.incX();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
	}
	hitbox.push_back(bomb->position());
	bomb->setHitbox(hitbox);

	_clock.removeObserver(bomb);
	this->removeObserver(bomb);
	if (std::find(_bombs[bomb->position()].begin(), _bombs[bomb->position()].end(), bomb) != _bombs[bomb->position()].end())
		_bombs[bomb->position()].erase(std::find(_bombs[bomb->position()].begin(), _bombs[bomb->position()].end(), bomb));

	this->notify(bomb, LEVEL_BOMB_EXPLODED);
}

/*
void
Level::toConfig(Config & cfg) const
{
	int	index;

	index = 0;
	cfg["charactersCount"] = _charactersCount;
	cfg["timeSpend"] = _clock.seconds();
	for (std::map<Position, std::list<Character*>>::const_iterator it = _characters.begin(); it != _characters.end(); it++)
		for (std::list<Character*>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); subIt++)
			(*it)->toConfig(cfg["characters"]);
	for (std::map<Position, std::list<Bomb*>>::const_iterator it = _bombs.begin(); it != _bombs.end(); it++)
		for (std::list<Bomb*>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); subIt++; index++)
			(*it)->toConfig(cfg["bombs"][index]);
	index = 0;
	for (std::map<Position, std::list<Item*>>::const_iterator it = _items.begin(); it != _items.end(); it++)
		for (std::list<Item*>::const_iterator subIt = it->second.begin(); subIt != it->second.end(); subIt++; index++)
			(*it)->toConfig(cfg["items"][index]);
}

void
Level::exportFile(const std::string & filename) const
{
	Config	cfg;

	toConfig(cfg);
	cfg.exportFile(filename);
}
*/
