/*
 * File:   Map.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:14 PM
 */

#include "Map.hpp"
#include "pugixml.hpp"
#include "global.hh"

Map::Map(size_t width, size_t height):
	_width(width), _height(height)
{
	_actions[LEVEL_BOMB_EXPLODED] = &Map::bombExploded;

	this->initMap();
	this->setBorders();
	this->setSolid();

	/*
	this->generateMap();
	this->delimitMap();
	this->oneOnTwo();
	this->placeDestrBlock();
	this->displayMap();
	*/
}

Map::Map(std::string const & mapFile, std::map<Position, std::list<Character* > > const &mymap)
{
	(void) mapFile;
	(void) mymap;
/*
	this->generateMap(mapFile);
	this->displayMap();
*/
}

Map::~Map()
{
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
Map::at(const Position& position) const
{
	return (this->_map[position.y()][position.x()]);
}

std::vector<std::vector<Block*> >
Map::map() const
{
	return (this->_map);
}

void
Map::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	(void)bomb;
}

void
Map::pushCharacter(Character* character)
{
	(void)character;
}

void
Map::initMap()
{
	_map.resize(_height);
	for (auto it = _map.begin(); it != _map.end(); ++it)
	{
		it->resize(_width);
	}
}

void
Map::setBorders()
{
	for (size_t y = 0; y < _height; ++y)
	{
		_map[y][0] = new Block(Position(0, y), g_settings["maps"]["default_blocks"]["wall"]);
		_map[y][_width - 1] = new Block(Position(_width - 1, y), g_settings["maps"]["default_blocks"]["wall"]);
	}
	for (size_t x = 0; x < _width; ++x)
	{
		_map[0][x] = new Block(Position(x, 0), g_settings["maps"]["default_blocks"]["wall"]);
		_map[_height - 1][x] = new Block(Position(x, _height - 1), g_settings["maps"]["default_blocks"]["wall"]);
	}

	for (size_t y = 1; y < _height - 1; ++y)
		for (size_t x = 1; x < _width - 1; ++x)
			_map[y][x] = new Block(Position(x, y), g_settings["maps"]["default_blocks"]["void"]);
}

void
Map::setSolid()
{

}

/*
void
Map::generateMap()
{
	if (_height < g_settings["maps"]["min_height"] || _width < g_settings["maps"]["min_width"])
		throw MapException("Map too small");

	_nbrBrick = (_height * _width) * 0.3;
	int y = 0;
	_map.resize(_height);
	for (std::vector<std::vector<Block*> >::const_iterator it = _map.begin(); it != _map.end(); it++)
	{
		_map[y].resize(_width);

		int x = 0;
		for (std::vector<int>::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
		{
			_map[y][x] = 0;
			x++;
		}
		y++;
	}
}

void
Map::generateMap(const std::string &file)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	if (result)
	{
		_width = doc.child("map").attribute("width").as_int();
		_height = doc.child("map").attribute("height").as_int();
		std::cout << _height << std::endl;
		std::cout << _width << std::endl;

		int y = 0;
		_map.resize(_height);
		for (pugi::xml_node row = doc.child("map").child("row"); row; row = row.next_sibling("row"))
		{
			int x = 0;
			_map[y].resize(_width);
			for (pugi::xml_node block = row.child("case"); block; block = block.next_sibling("case"))
			{
				std::string entity = block.attribute("entity").value();
				if (entity == "wall")
					_map[y][x] = SOLID;
				else if (entity == "floor")
					_map[y][x] = EMPTY;
				else if (entity == "block")
					_map[y][x] = DESTR;
				else
					throw MapException("XML : incorrect file");
				x++;
			}
			y++;
		}
	}
	else
		throw MapException("Can't open the file");
}

void
Map::checkPositionPlayer()
{
	int x;
	int y;

	for (std::map<Position, std::list<Character* > >::iterator it = this->_m.begin(); it != this->_m.end(); it++)
	{
		x = it->first.x();
		y = it->first.y();
		_map[y][x] = 8;
		if (x + 1 < _width)
			if (_map[y][x + 1] != SOLID)
				_map[y][x + 1] = EMPTY;
		if (x - 1 > 1)
			if (_map[y][x - 1] != SOLID)
				_map[y][x - 1] = EMPTY;
		if (y + 1 < _height)
			if (_map[y + 1][x] != SOLID)
				_map[y + 1][x] = EMPTY;
		if (y - 1 > 1)
			if (_map[y - 1][x] != SOLID)
				_map[y - 1][x] = EMPTY;
	}
}

void
Map::delimitMap()
{
	int i;

	for (i = 0; i < this->_width; i++)
	{
		this->_map[0][i] = SOLID;
		this->_map[this->_height - 1][i] = SOLID;
	}
	for (i = 0; i < this->_height; i++)
	{
		this->_map[i][0] = SOLID;
		this->_map[i][this->_width - 1] = SOLID;
	}
}

void
Map::oneOnTwo()
{
	bool i;

	for (int j = 2; j < this->_height - 1; j++)
	{
		if (!(j % 2))
		{
			i = false;
			for (int k = 1; k < this->_width - 1; k++)
			{
				if (i)
					this->_map[j][k] = SOLID;
				i = !i;
			}
		}
	}
}

void
Map::displayMap()
{
	for (std::vector<std::vector<int> >::const_iterator it = this->_map.begin(); it != this->_map.end(); it++)
	{
		for (std::vector<int>::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2;
		std::cout << std::endl;
	}
}

void
Map::placeDestrBlock()
{
	int x = 0;
	int y = 0;

	srand(time(NULL));
	while (this->_nbrBrick > 0)
	{
		while (this->_map[y][x] != EMPTY)
		{
			x = rand() % this->_width;
			y = rand() % this->_height;
		}
		this->_map[y][x] = DESTR;
		_nbrBrick -= 1;
	}
}
*/