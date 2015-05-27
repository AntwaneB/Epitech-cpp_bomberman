/*
 * File:   Map.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:14 PM
 */

#include "Core/Map.hh"
#include "Core/Bomb.hh"
#include "pugixml.hpp"
#include "global.hh"

Map::Map(size_t width, size_t height):
	_width(width), _height(height)
{
	_actions[LEVEL_BOMB_EXPLODED] = &Map::bombExploded;
	_actions[BLOCK_DESTROYED] = &Map::blockDestroyed;

	this->initMap();
	this->setBorders();
	this->setSolid();
	this->setDestructible();
	this->bindBlocks();
}

Map::Map(std::string const & mapFile)
{
	this->loadFromFile(mapFile);
}

Map::~Map()
{
	for (size_t y = 0; y < _map.size(); ++y)
	{
		for (size_t x = 0; x < _map[y].size(); ++x)
		{
			delete _map[y][x];
		}
	}
}

size_t
Map::width() const
{
	return (_width);
}

size_t
Map::height() const
{
	return (_height);
}

Block*
Map::at(const Position<>& position) const
{
	return (this->_map[position.y()][position.x()]);
}

std::vector<std::vector<Block*> > const &
Map::map() const
{
	return (this->_map);
}

void
Map::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	this->notify(bomb, MAP_BOMB_EXPLODED);
}

void
Map::blockDestroyed(Subject* entity)
{
	Block* block = safe_cast<Block*>(entity);

	for (auto it = _map.begin(); it != _map.end(); ++it)
	{
		for (auto iit = it->begin(); iit != it->end(); ++iit)
		{
			if (*iit == block)
			{
				*iit = new Block(block->position(), g_settings["maps"]["default_blocks"]["void"]);
				this->addObserver(*iit);
				(*iit)->addObserver(this);
			}
		}
	}

	this->notify(block, MAP_BLOCK_DESTROYED);
	this->removeObserver(block);
}

void
Map::replaceAt(const Position<>& position, Block* block)
{
	Block* toRemove = _map[position.y()][position.x()];

	this->removeObserver(toRemove);
	delete toRemove;
	_map[position.y()][position.x()] = block;
}

void
Map::pushCharacter(const Character* character)
{
	Block* block = _map[character->position().y()][character->position().x()];

	if (block->solid() || block->visible())
		this->replaceAt(Position<>(character->position().x(), character->position().y()), new Block(character->position(), g_settings["maps"]["default_blocks"]["void"]));

	std::map<std::pair<Position<>, Position<> >, bool> freePath;
	Position<> up(character->position().x(), character->position().y() - 1);
	Position<> down(character->position().x(), character->position().y() + 1);
	Position<> left(character->position().x() - 1, character->position().y());
	Position<> right(character->position().x() + 1, character->position().y());

	if (up.y() > 0 && right.x() < (int)_width - 1)
		freePath[{ up, right }] = false;
	if (right.x() < (int)_width - 1 && down.y() < (int)_height - 1)
		freePath[{ right, down }] = false;
	if (down.y() < (int)_height - 1 && left.x() > 0)
		freePath[{ down, left }] = false;
	if (left.x() > 0 && up.y() > 0)
		freePath[{ left, up }] = false;

	int count = 0;
	for (auto it = freePath.begin(); it != freePath.end(); ++it)
	{
		if (!this->at(it->first.first)->solid() && !this->at(it->first.first)->visible()
			&& !this->at(it->first.second)->solid() && !this->at(it->first.second)->visible())
		{
			it->second = true;
			count++;
		}
	}

	if (count == 0)
	{
		Position<> first = (*(freePath.begin())).first.first;
		Position<> second = (*(freePath.begin())).first.second;

		this->replaceAt(first, new Block(character->position(), g_settings["maps"]["default_blocks"]["void"]));
		this->replaceAt(second, new Block(character->position(), g_settings["maps"]["default_blocks"]["void"]));
	}
}

void
Map::initMap()
{
	_map.resize(_height);
	for (auto it = _map.begin(); it != _map.end(); ++it)
	{
		it->resize(_width);
		for (auto block = it->begin(); block != it->end(); ++block)
			*block = NULL;
	}
}

void
Map::setBorders()
{
	for (size_t y = 1; y < _height - 1; ++y)
	{
		_map[y][0] = new Block(Position<>(0, y), g_settings["maps"]["default_blocks"]["wall"]);
		_map[y][_width - 1] = new Block(Position<>(_width - 1, y), g_settings["maps"]["default_blocks"]["wall"]);
	}
	for (size_t x = 0; x < _width; ++x)
	{
		_map[0][x] = new Block(Position<>(x, 0), g_settings["maps"]["default_blocks"]["wall"]);
		_map[_height - 1][x] = new Block(Position<>(x, _height - 1), g_settings["maps"]["default_blocks"]["wall"]);
	}
}

void
Map::setSolid()
{
	for (size_t y = 2; y < _height - 1; y += 2)
	{
		for (size_t x = 2; x < _width - 1; x += 2)
		{
			if (y % 2 == 0 && x % 2 == 0)
				_map[y][x] = new Block(Position<>(x, y), g_settings["maps"]["default_blocks"]["wall"]);
		}
	}
}

void
Map::setDestructible()
{
	for (size_t y = 1; y < _height - 1; ++y)
	{
		for (size_t x = 1; x < _width - 1; ++x)
		{
			if (_map[y][x] == NULL)
			{
				if (rand() % 100 < 75)
					_map[y][x] = new Block(Position<>(x, y), g_settings["maps"]["default_blocks"]["box"]);
				else
					_map[y][x] = new Block(Position<>(x, y), g_settings["maps"]["default_blocks"]["void"]);
			}
		}
	}
}

void
Map::bindBlocks()
{
	for (auto row = _map.begin(); row != _map.end(); ++row)
	{
		for (auto block = row->begin(); block != row->end(); ++block)
		{
			this->addObserver(*block);
			(*block)->addObserver(this);
		}
	}
}

void
Map::loadFromFile(const std::string & mapFile)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(mapFile.c_str());

	if (result)
	{
		_width = doc.child("map").attribute("width").as_int();
		_height = doc.child("map").attribute("height").as_int();

		_map.resize(_height);

		int y = 0;
		for (pugi::xml_node row = doc.child("map").child("row"); row; row = row.next_sibling("row"))
		{
			_map[y].resize(_width);

			int x = 0;
			for (pugi::xml_node block = row.child("case"); block; block = block.next_sibling("case"))
			{
				std::string entity = block.attribute("entity").value();
				_map[y][x] = new Block(Position<>(x, y), entity);
				x++;
			}
			y++;
		}
	}
	else
		throw MapException("Can't open the file");
}
