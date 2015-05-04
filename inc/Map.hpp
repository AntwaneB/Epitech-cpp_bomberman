/*
 * File:   Map.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:14 PM
 */

#ifndef MAP_HPP
#define	MAP_HPP

#include <string>
#include <iostream>
#include "IEntity.hpp"
#include "Observer.hpp"

#define EMPTY 0;
#define	SOLID 1;
#define DESTR 2;

class Map : public IEntity, public Observer, public Subject
{
public:
	Map(size_t width, size_t height);
	Map(std::string const & mapFile);
	virtual ~Map();

	virtual void onNotify(IEntity const & entity, Event event);

protected:
	void	generatemap();
	void 	displaymap();
	int 	**getmap();

private:
	void 	delimitMap();
	int **_map;
	int _height;
	int _width;

};

#endif	/* MAP_HPP */
