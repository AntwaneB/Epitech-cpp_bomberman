/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#include <cmath>
#include "global.hh"
#include "Exception.hpp"
#include "misc/StdHelper.hpp"
#include "Core/Level.hh"
#include "Core/Input.hh"
#include "Core/RangeIncreaser.hh"
#include "Core/Save.hh"
#include "Core/Menu.hh"
#include "Core/Monster.hh"

Level::Level(size_t width, size_t height, size_t charactersCount, size_t playersCount, IA::Difficulty difficulty)
	: _map(width, height), _charactersCount(charactersCount), _playersCount(playersCount),
	  _secondsElapsed(0), _charactersKills(0), _difficulty(difficulty)
{
	_actions[CLOCK_TICK] = &Level::tick;
	_actions[CLOCK_PAUSE_TICK] = &Level::pauseTick;
	_actions[CHARACTER_MOVED] = &Level::characterMoved;
	_actions[CHARACTER_DIED] = &Level::characterDied;
	_actions[MONSTER_MOVED] = &Level::monsterMoved;
	_actions[MONSTER_DIED] = &Level::monsterDied;
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

	this->pushMonster();
}

Level::Level(Config cfg)
	: _map(cfg["map"]), _clock(cfg["clock"])
{
	_actions[CLOCK_TICK] = &Level::tick;
	_actions[CLOCK_PAUSE_TICK] = &Level::pauseTick;
	_actions[CHARACTER_MOVED] = &Level::characterMoved;
	_actions[CHARACTER_DIED] = &Level::characterDied;
	_actions[MONSTER_MOVED] = &Level::monsterMoved;
	_actions[MONSTER_DIED] = &Level::monsterDied;
	_actions[ITEM_DROPPED] = &Level::itemDropped;
	_actions[ITEM_MOVED] = &Level::itemMoved;
	_actions[ITEM_DESTROYED] = &Level::itemDestroyed;
	_actions[BOMB_DROPPED] = &Level::bombDropped;
	_actions[BOMB_EXPLODED] = &Level::bombExploded;
	_actions[MAP_BLOCK_DESTROYED] = &Level::blockDestroyed;
	_actions[KEY_PRESSED] = &Level::keyPressed;
	_actions[EXIT_TRIGGERED] = &Level::quitLevel;

//	_items;
//	_explosions;
	_charactersCount = cfg["charactersCount"];
	_playersCount = cfg["playersCount"];
	_secondsElapsed = cfg["secondsElapsed"];
//	for (auto it = cfg["scores"].begin(); it != cfg["scores"].end(); ++it)
//		_scores.push_back(new Character(it->second));
	_charactersKills = cfg["charactersKills"];

	_clock.addObserver(this);
	this->addObserver(&_map);
	_map.addObserver(this);
//	_difficulty;

	for (auto it = cfg["items"].begin(); it != cfg["items"].end(); ++it)
	{
		Item*	item = new Item(it->second["item"]);
		_items[item->position()].push_back(item);
		item->addObserver(this);
		_clock.addObserver(item);
		this->addObserver(item);
	}

	for (auto it = cfg["characters"].begin(); it != cfg["characters"].end(); ++it)
	{
		Character*	character = new Character(this, it->second["character"]);
		_scores.push_back(character);
		_characters[character->position()].push_back(character);
		if (character->isPlayer())
			_players.push_back(character);

		character->addObserver(this);
		_clock.addObserver(character);
		this->addObserver(character);
	}

	for (auto it = cfg["monsters"].begin(); it != cfg["monsters"].end(); ++it)
	{
		Monster*	monster = new Monster(this, it->second["monster"]);
		_monsters[monster->position()].push_back(monster);
		monster->addObserver(this);
		_clock.addObserver(monster);
		this->addObserver(monster);
	}

	for (auto it = cfg["bombs"].begin(); it != cfg["bombs"].end(); ++it)
	{
		Position<> pos(it->second["position"]);
		Bomb* bomb = new Bomb(it->second["bomb"]);
		this->bombDropped(bomb);
//		_bombs[pos].push_back(bomb);
	}
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

std::map<Position<>, std::list<Character*> > const &
Level::characters() const
{
	return (_characters);
}

std::map<Position<>, std::list<Monster*> > const &
Level::monsters() const
{
	return (_monsters);
}

std::list<Character*> const &
Level::players() const
{
	return (_players);
}

std::vector<Character*> const
Level::charactersRaw() const
{
	return (StdHelper::flatten<Character*, Position<> >(_characters));
}

std::vector<Monster*> const
Level::monstersRaw() const
{
	return (StdHelper::flatten<Monster*, Position<> >(_monsters));
}

std::vector<Bomb*> const
Level::bombsRaw() const
{
	return (StdHelper::flatten<Bomb*, Position<>>(_bombs));
}

std::vector<BonusItem*> const
Level::itemsRaw() const
{
	return (StdHelper::flatten<BonusItem*, Position<> >(_items));
}

std::map<Position<>, std::list<Bomb *> > const &
Level::bombs() const
{
	return _bombs;
}

std::list<Bomb::Explosion>
Level::explosions() const
{
	return (_explosions);
}

const Character*
Level::winner() const
{
	return (_winner);
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

	int y;
	int i = y = 0;
	for (auto it = _scores.begin(); it != _scores.end(); ++it)
	{
		std::cout << ((*it)->isPlayer() ? "Player " : "IA ") << ((*it)->isPlayer() ? ++i : ++y) << " : " << (*it)->score() << " points" << std::endl;
	}
	std::cout << std::endl;

	_winner = NULL;
	for (auto it = _scores.begin(); it != _scores.end(); ++it)
	{
		if ((*it)->alive() && (_winner == NULL || (*it)->score() > _winner->score()))
			_winner = *it;
	}

	this->notify(this, LEVEL_ENDED);
}

void
Level::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);
	if (clock == &_clock)
	{
		for (auto it = _explosions.begin(); it != _explosions.end(); ++it)
		{
			if (_clock.seconds() >= it->lastUntil)
			{
				it = _explosions.erase(it);
				--it;
			}
		}

		this->notify(this, LEVEL_UPDATED);

		if (static_cast<size_t>(_clock.seconds()) > _secondsElapsed)
		{ // Updating characters score
			_secondsElapsed++;

			for (auto it = _scores.begin(); it != _scores.end(); ++it)
				if ((*it)->alive())
					(*it)->changeScore(g_settings["scores"]["second_elapsed"]);

			// Spawning monster
			if (rand() % 1000 < static_cast<int>(g_settings["entities"]["monster"]["spawn_chance"]))
			{
				this->pushMonster();
			}
		}

		if (this->charactersRaw().size() <= 1
			|| (std::count_if(_players.begin(), _players.end(), [](Character* ptr) { return (ptr == NULL); }) == static_cast<int>(_players.size())
				&& _players.size() != 0))
		{ // Ending game if their's only one character or no player left
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
	size_t id = isPlayer ? _players.size() + 1 : _characters.size() - _players.size() + 1;
	Character*	character = new Character(this, id, isPlayer, _difficulty, charX, charY);
	character->addObserver(this);

	_scores.push_back(character);
	_characters[Position<>(charX, charY)].push_back(character);
	if (isPlayer)
		_players.push_back(character);

	_clock.addObserver(character);
	this->addObserver(character);

	return (character);
}

Monster*
Level::pushMonster()
{
	int x = rand() % (_map.width() - 2) + 2;
	int y = rand() % (_map.height() - 2) + 2;
	Monster* monster = new Monster(this, Position<>(x, y));

	_monsters[monster->position()].push_back(monster);

	_clock.addObserver(monster);
	this->addObserver(monster);
	monster->addObserver(this);

	return (monster);
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
		if (killer != _scores.end())
		{
			if (*killer != character)
				(*killer)->changeScore(g_settings["scores"][_charactersKills == 0 ? "first_blood" : "character_kill"]);
			else
				(*killer)->changeScore(g_settings["scores"]["self_kill"]);
		}
		_charactersKills++;
	}
}

void
Level::monsterMoved(Subject* entity)
{
	Monster* monster = safe_cast<Monster*>(entity);

	_monsters[monster->prevPosition()].erase(std::find(_monsters[monster->prevPosition()].begin(), _monsters[monster->prevPosition()].end(), monster));
	_monsters[monster->position()].push_back(monster);
}

void
Level::monsterDied(Subject* entity)
{
	Monster* monster = safe_cast<Monster*>(entity);

	_monsters[monster->position()].erase(std::find(_monsters[monster->position()].begin(), _monsters[monster->position()].end(), monster));
	_clock.removeObserver(monster);
	this->removeObserver(monster);

	if (monster->killedBy())
	{
		auto killer = std::find(_scores.begin(), _scores.end(), monster->killedBy()->owner());
		if (killer != _scores.end())
		{
			(*killer)->changeScore(g_settings["scores"]["monster_kill"]);
		}
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
	std::vector<Position<> > hitbox;
	size_t range = bomb->range();

	Position<> explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.decY();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
		if (_map.at(explosion)->solid())
			break;
	}
	explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.incY();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
		if (_map.at(explosion)->solid())
			break;
	}
	explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.decX();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
		if (_map.at(explosion)->solid())
			break;
	}
	explosion = bomb->position();
	for (size_t i = 0; i < range; i++)
	{
		explosion.incX();
		if (explosion.outOfBounds(_map.width(), _map.height()) || _map.at(explosion)->blockBombs())
			break;
		hitbox.push_back(explosion);
		if (_map.at(explosion)->solid())
			break;
	}
	hitbox.push_back(bomb->position());
	bomb->setHitbox(hitbox);

	_clock.removeObserver(bomb);
	this->removeObserver(bomb);
	if (std::find(_bombs[bomb->position()].begin(), _bombs[bomb->position()].end(), bomb) != _bombs[bomb->position()].end())
		_bombs[bomb->position()].erase(std::find(_bombs[bomb->position()].begin(), _bombs[bomb->position()].end(), bomb));

	//Bomb::Explosion explosion(_clock.seconds() + 1, hitbox);
	_explosions.push_back(Bomb::Explosion(_clock.seconds() + 1, hitbox));

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
	static seconds_t previousSave = -1;
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
		else if (input->key() == Input::SAVE && _clock.seconds() - previousSave >= 5)
		{
			previousSave = _clock.seconds();
			std::cout << "Saving level to file..." << std::endl;

			Save	save(this, "./saves/save.xml");
			save.save();
		}
	}
}

void
Level::quitLevel(Subject* entity __attribute__((unused)))
{
	this->end();
}
