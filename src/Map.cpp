/*
 * File:   Map.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:14 PM
 */

#include "Map.hpp"

int main()
{
	Map m(20, 20);

}

Map::Map(size_t width, size_t height): _width(width), _height(height)
{
	std::cout << "Loading..." << std::endl;
	this->generatemap();
	this->displaymap();
}

Map::Map(std::string const & mapFile)
{
	this->generatemap();
}

Map::~Map()
{

}

void	Map::generatemap()
{
	int i;
	int j;

	i = 0;
	this->_map = new int *[_height];
	for (i = 0; i < this->_width; i++)
		this->_map[i] = new int[this->_width];
	for (i = 0; i < this->_height; i++)
	{
		for (j = 0; j < this->_width; j++)
			this->_map[i][j] = 0;
	}
	this->delimitMap();
}

void Map::delimitMap()
{
	int i;

	for (i = 0; i < this->_width; i++)
		this->_map[0][i] = SOLID;
}

void Map::displaymap()
{	
	for (int i = 0; i < this->_height; i++)
	{
		for (int j = 0; j < this->_width; j++)
			std::cout << this->_map[i][j];
		std::cout << std::endl;
	}
}

int  **Map::getmap()
{
	return (this->_map);
}

void Map::onNotify(const IEntity& entity, Event event)
{
	(void)entity;
	(void)event;
}

