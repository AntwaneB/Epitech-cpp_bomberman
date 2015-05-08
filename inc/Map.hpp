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
#include <vector>
#include "Character.hpp"
#include "Position.hpp"
#include "Observer.hpp"
#include "Exception.hpp"

#define EMPTY 0
#define SOLID 1
#define DESTR 2

#define MAP_MIN_X 10
#define MAP_MIN_Y 10

class Map : public Subject, public Observer
{
public:
	Map(size_t, size_t);
	Map(size_t, size_t, std::map<Position, std::list<Character* > > const &);
	Map(std::string const & mapFile, std::map<Position, std::list<Character* > > const &);
	virtual ~Map();

	virtual void onNotify(Subject * entity, Event event);

	void	pushCharacter(Character*);

	size_t	width() const;
	size_t	height() const;

	void	generateMap();
	void 	generateMap(const std::string &);

	std::vector<std::vector<int> > getMap();

private:
	void 	displayMap();
	void 	delimitMap();
	void 	placeDestrBlock();
	void 	oneOnTwo();
	void 	checkPositionPlayer();

private:
	int 	_width;
	int 	_height;
	int 	_nbrBrick;
	std::vector<std::vector<int> > _map;
	std::map<Position, std::list<Character*> > _m;
};

#endif	/* MAP_HPP */
