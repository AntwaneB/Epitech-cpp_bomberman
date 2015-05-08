/*
 * File:   Map.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:14 PM
 */

#include "Map.hpp"
#include "pugixml.hpp"

Map::Map(size_t width, size_t height):
	_width(width), _height(height)
{
	this->generateMap();
	this->delimitMap();
	this->oneOnTwo();
	this->placeDestrBlock();
	this->displayMap();
}

Map::Map(size_t width, size_t height, std::map<Position, std::list<Character *> > const &map):
	_width(width), _height(height), _m(map)
{
	this->generateMap();
	this->delimitMap();
	this->oneOnTwo();
	this->placeDestrBlock();
	this->checkPositionPlayer();
	this->displayMap();
}

Map::Map(std::string const & mapFile, std::map<Position, std::list<Character* > > const &mymap)
{
	(void) mapFile;
	(void) mymap;
	this->generateMap(mapFile);
	this->displayMap();
}

Map::~Map()
{

}

void
Map::onNotify(Subject * entity, Event event)
{
	(void)entity;
	(void)event;
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

std::vector<std::vector<int> >
Map::getMap()
{
	return (this->_map);
}

void
Map::pushCharacter(Character* character)
{
	(void)character;
}

void
Map::generateMap(const std::string &file)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	int y;
	int x;

	if (result)
	{
		this->_width = doc.child("map").attribute("width").as_int();
		this->_height = doc.child("map").attribute("height").as_int();
		std::cout << this->_height << std::endl;
		std::cout << this->_width << std::endl;

		y = 0;
		this->_map.resize(this->_height);
		for (pugi::xml_node row = doc.child("map").child("row"); row; row = row.next_sibling("row"))
		{
			x = 0;
			this->_map[y].resize(this->_width);
			for (pugi::xml_node block = row.child("case"); block; block = block.next_sibling("case"))
			{
				std::string entity = block.attribute("entity").value();
				if (entity == "wall")
					this->_map[y][x] = SOLID;
				else if (entity == "floor")
					this->_map[y][x] = EMPTY;
				else if (entity == "block")
					this->_map[y][x] = DESTR;
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
Map::generateMap()
{
	int y;
	int x;

	if (this->_height < MAP_MIN_Y || this->_width < MAP_MIN_X)
		throw MapException("Map to little");
	_nbrBrick = (this->_height * this->_width) * 0.3;
	y = 0;
	this->_map.resize(this->_height);
	for (std::vector<std::vector<int> >::const_iterator it = this->_map.begin(); it != this->_map.end(); it++)
	{
		x = 0;
		this->_map[y].resize(this->_width);
		for (std::vector<int>::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
		{
			this->_map[y][x] = 0;
			x++;
		}
		y++;
	}
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
		this->_map[y][x] = 8;
		if (x + 1 < this->_width)
			if (this->_map[y][x + 1] != SOLID)
				this->_map[y][x + 1] = EMPTY;
		if (x - 1 > 1)
			if (this->_map[y][x - 1] != SOLID)
				this->_map[y][x - 1] = EMPTY;
		if (y + 1 < this->_height)
			if (this->_map[y + 1][x] != SOLID)
				this->_map[y + 1][x] = EMPTY;
		if (y - 1 > 1)
			if (this->_map[y - 1][x] != SOLID)
				this->_map[y - 1][x] = EMPTY;
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
