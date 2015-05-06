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
#include <cstdlib>
#include <ctime>
#include "Character.hpp"
#include "Position.hpp"
#include "Observer.hpp"
#include "Exception.hpp"


#define EMPTY 0
#define	SOLID 1
#define DESTR 2

#define MAP_MIN_X 10
#define MAP_MIN_Y 10

class Map : public Subject, public Observer
{
public:
	Map(size_t, size_t, std::map<Position *, int> const &);
	Map(std::string const & mapFile, std::map<Position *, int> const &);
	virtual ~Map();

	virtual void onNotify(Subject * entity, Event event);

protected:
	void	generateMap();
	void 	displayMap();
	int 	**getMap();

private:
	void 	delimitMap();
	void 	placeDestrBlock();
	void 	oneOnTwo();
	void 	checkArg();
	void 	checkPositionPlayer();
	int 	**_map;
	int 	_width;
	int 	_height;
	int 	_nbrBrick;
	std::map<Position *, int> _m;

};

#endif	/* MAP_HPP */
