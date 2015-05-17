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
#include "Block.hh"
#include "Exception.hpp"

#define EMPTY 0
#define SOLID 1
#define DESTR 2

class Map :  public EventHandler<Map>, public Subject
{
public:
	Map(size_t, size_t);
	Map(std::string const & mapFile, std::map<Position, std::list<Character* > > const &);
	virtual ~Map();

	void	pushCharacter(const Character*);

	size_t	width() const;
	size_t	height() const;
	std::vector<std::vector<Block*> > map() const;
	Block*	at(Position const &) const;

private:
	void	initMap();
	void	setBorders();
	void	setSolid();
	void	setDestructible();
	void	bindBlocks();

private:
	void	bombExploded(Subject*);
	void	blockDestroyed(Subject*);

/*
	void	generateMap();
	void 	generateMap(const std::string &);
	void 	displayMap();
	void 	delimitMap();
	void 	placeDestrBlock();
	void 	oneOnTwo();
	void 	checkPositionPlayer();
*/

private:
	size_t	_width;
	size_t	_height;
	int 	_nbrBrick;
	std::vector<std::vector<Block*> > _map;
	std::map<Position, std::list<Character*> > _m;
};

#endif	/* MAP_HPP */
