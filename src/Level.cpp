/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#include "global.hh"
#include "Exception.hpp"
#include "misc/StdHelper.hpp"
#include "Core/Level.hh"
#include "Core/Input.hh"
#include "Core/RangeIncreaser.hh"

Level::Level(size_t width, size_t height, size_t charactersCount, size_t playersCount)
	: _map(width, height), _charactersCount(charactersCount), _playersCount(playersCount), _secondsElapsed(0), _charactersKills(0)
{
	_actions[CLOCK_TICK] = &Level::tick;
	_actions[CLOCK_PAUSE_TICK] = &Level::pauseTick;
	_actions[CHARACTER_MOVED] = &Level::characterMoved;
	_actions[CHARACTER_DIED] = &Level::characterDied;
	_actions[ITEM_DROPPED] = &Level::itemDropped;
	_actions[ITEM_MOVED] = &Level::itemMoved;
	_actions[ITEM_DESTROYED] = &Level::itemDestroyed;
	_actions[BOMB_DROPPED] = &Level::bombDropped;
	_actions[BOMB_EXPLODED] = &Level::bombExploded;
	_actions[MAP_BLOCK_DESTROYED] = &Level::blockDestroyed;
	_actions[KEY_PRESSED] = &Level::keyPressed;
	_actions[EXIT_TRIGGERED] = &Level::quitLevel;

	_clock.addObserver(this);

	this->addObserver(&_map);
	_map.addObserver(this);

	for (size_t i = 0; i < charactersCount; i++)
	{
		_map.pushCharacter(this->pushCharacter());
	}

	/* Pushing a lot of elements to test graphical perfs
	for (size_t y = 0; y < _map.height(); ++y)
	{
		for (size_t x = 0; x < _map.width(); ++x)
		{
			_items[Position(x, y)].push_back(new RangeIncreaser(Position(x, y)));
			_bombs[Position(x, y)].push_back(new Bomb(Position(x, y), 2, 4, NULL));
		}
	}
	*/
}

Level::~Level()
{
	for (auto it = _characters.begin(); it != _characters.end(); ++it)
		for (auto yt = (*it).second.begin(); yt != (*it).second.end(); ++yt)
			delete *yt;

	for (auto it = _bombs.begin(); it != _bombs.end(); ++it)
		for (auto yt = (*it).second.begin(); yt != (*it).second.end(); ++yt)
			delete *yt;

	for (auto it = _items.begin(); it != _items.end(); ++it)
		for (auto yt = (*it).second.begin(); yt != (*it).second.end(); ++yt)
			delete *yt;
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

std::list<Character*> const &
Level::players() const
{
	return (_players);
}

std::vector<Character*> const
Level::charactersRaw() const
{
	return (StdHelper::flatten<Character*, Position>(_characters));
}

std::vector<Bomb*> const
Level::bombsRaw() const
{
	return (StdHelper::flatten<Bomb*, Position>(_bombs));
}

std::vector<BonusItem*> const
Level::itemsRaw() const
{
	return (StdHelper::flatten<BonusItem*, Position>(_items));
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
Level::end()
{
	std::cout << std::endl << "#### Scores ####" << std::endl;

	int i = 1;
	for (auto it = _scores.begin(); it != _scores.end(); ++it)
	{
		if ((*it)->isPlayer())
		{
			std::cout << "Player " << i << " : " << (*it)->score() << " points" << std::endl;
			i++;
		}
	}
}

void
Level::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);
	if (clock == &_clock)
	{
		this->notify(this, LEVEL_UPDATED);

		if (static_cast<size_t>(_clock.seconds()) > _secondsElapsed)
		{ // Updating characters score
			_secondsElapsed++;

			for (auto it = _scores.begin(); it != _scores.end(); ++it)
				(*it)->changeScore(g_settings["scores"]["second_elapsed"]);
		}

		if (this->charactersRaw().size() <= 1)
		{ // Ending game if their's only one character left
			_clock.stop();
			this->end();
		}
	}
}

void
Level::pauseTick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);
	if (clock == &_clock)
	{
		this->notify(this, LEVEL_PAUSE_TICK);
	}
}

Character*
Level::pushCharacter()
{
	// Getting character spawn coordinates
	size_t blocksPerLine = _map.width() >= _map.height() ? ceil(sqrt(_charactersCount)) : floor(sqrt(_charactersCount));
	size_t lines = _map.width() >= _map.height() && sqrt(_charactersCount) != static_cast<int>(sqrt(_charactersCount)) ? ceil(sqrt(_charactersCount)) : ceil(sqrt(_charactersCount));

	if (blocksPerLine * lines >= _charactersCount + blocksPerLine)
		lines--;

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

	// Getting isPlayer
	bool isPlayer = false;

	if (_playersCount == 1)
		isPlayer = nth == _charactersCount / 2;
	else if (_playersCount == 2)
		isPlayer = nth == 0 || nth == _charactersCount - 1;
	else
	{
		size_t step = round(_charactersCount / static_cast<float>(_playersCount));
		if (_players.size() < _playersCount && (nth % step == 0 || nth + 1 == _charactersCount))
			isPlayer = true;
	}

	// Creating new character
	Character*	character = new Character(this, nth + 1, isPlayer, charX, charY);
	character->addObserver(this);

	_scores.push_back(character);
	_characters[Position(charX, charY)].push_back(character);
	if (isPlayer)
		_players.push_back(character);

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

	while (!_items[character->position()].empty())
	{
		BonusItem* item = _items[character->position()].front();

		item->applyEffect(character);
		character->changeScore(g_settings["scores"]["item_picked"]);
	}
}

void
Level::characterDied(Subject* entity)
{
	Character* character = safe_cast<Character*>(entity);

	_characters[character->position()].erase(std::find(_characters[character->position()].begin(), _characters[character->position()].end(), character));
	_clock.removeObserver(character);
	this->removeObserver(character);

	auto it = std::find(_players.begin(), _players.end(), character);
	if (it != _players.end())
		*it = NULL;

	if (character->killedBy())
	{
		auto killer = std::find(_scores.begin(), _scores.end(), character->killedBy()->owner());
		if (killer != _scores.end() && *killer != character)
			(*killer)->changeScore(g_settings["scores"][_charactersKills == 0 ? "first_blood" : "character_kill"]);
		_charactersKills++;
	}
}

void
Level::itemDropped(Subject* entity)
{
	BonusItem* item = safe_cast<BonusItem*>(entity);

	_items[item->position()].push_back(item);
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
Level::itemDestroyed(Subject* entity)
{
	BonusItem* item = safe_cast<BonusItem*>(entity);

	_items[item->position()].erase(std::find(_items[item->position()].begin(), _items[item->position()].end(), item));
	_clock.removeObserver(item);
	this->removeObserver(item);
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

void
Level::blockDestroyed(Subject* entity)
{
	Block* block = safe_cast<Block*>(entity);

	if (rand() % 100 < static_cast<int>(g_settings["entities"]["bonus_item"]["drop_chance"]))
	{ // We decide to create a random item
		Item::Type type = static_cast<Item::Type>(rand() % Item::last);

		BonusItem* item = BonusItem::factory(type, block->position());
		this->itemDropped(item);
	}
}

void
Level::keyPressed(Subject* entity)
{
	Input* input = safe_cast<Input*>(entity);

	if (input->key() > Input::KEYS_P1_START && input->key() < Input::KEYS_P1_END && _players.size() >= 1)
	{
		auto it = _players.begin();
		std::advance(it, 0);
		if (*it != NULL)
			this->notify(input, KEY_PRESSED, *it);
	}
	else if (input->key() > Input::KEYS_P2_START && input->key() < Input::KEYS_P2_END && _players.size() >= 2)
	{
		auto it = _players.begin();
		std::advance(it, 1);
		if (*it != NULL)
			this->notify(input, KEY_PRESSED, *it);
	}
	else
	{
		if (input->key() == Input::PAUSE)
		{
			_clock.togglePause();
		}
	}
}

void
Level::quitLevel(Subject* entity __attribute__((unused)))
{
	delete this;
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
