/*
 * File:   Map.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:14 PM
 */

#include "Map.hpp"

Map::Map(size_t width, size_t height): _width(width), _height(height)
{
	std::cout << "Loading..." << std::endl;
	this->generateMap();
	this->displayMap();
}

Map::Map(std::string const & mapFile)
{
	(void) mapFile;
	this->generateMap();
}

Map::~Map()
{

}

void 	Map::checkArg()
{
	if (this->_height < MAP_MIN_Y || this->_width < MAP_MIN_X)
		throw MapException("Map to little");
	if (!(this->_height % 2))
		this->_height += 1;
	if (!(this->_width % 2))
		this->_width += 1;
}

void	Map::generateMap()
{
	int i;
	int j;

	this->checkArg();
	_nbrBrick = (this->_height * this->_width) * 0.3;
	this->_map = new int *[_height];
	for (i = 0; i < this->_width; i++)
		this->_map[i] = new int[this->_width];
	for (i = 0; i < this->_height; i++)
	{
		for (j = 0; j < this->_width; j++)
			this->_map[i][j] = 0;
	}
	this->delimitMap();
	this->oneOnTwo();
	this->placeDestrBlock();
	this->checkPositionPlayer();
}

void Map::checkPositionPlayer()
{

}

void Map::delimitMap()
{
	int i;

	for (i = 0; i < this->_width; i++)
	{
		this->_map[0][i] = SOLID;
		this->_map[i][0] = SOLID;
	}
	for (i = 0; i < this->_height; i++)
	{
		this->_map[this->_height - 1][i] = SOLID;
		this->_map[i][this->_height - 1] = SOLID;
	}
}

void Map::oneOnTwo()
{
	bool i;

	for (int j = 1; j < this->_height - 1; j++)
	{
		if (j % 2)
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

void Map::displayMap()
{
	for (int i = 0; i < this->_height; i++)
	{
		for (int j = 0; j < this->_width; j++)
			std::cout << this->_map[i][j];
		std::cout << std::endl;
	}
}

void Map::placeDestrBlock()
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
	}
}


int  **Map::getMap()
{
	return (this->_map);
}

void Map::onNotify(const Subject& entity, Event event)
{
	(void)entity;
	(void)event;
}

