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
#include "Character.hh"
#include "Position.hh"
#include "Observer.hpp"
#include "Block.hh"
#include "Exception.hpp"

class Map :  public EventHandler<Map>, public Subject
{
	friend class	Save;

public:
	Map(size_t, size_t);
	Map(std::string const & mapFile);
	Map(Config::Param);
	virtual ~Map();

	void	pushCharacter(const Character*);

	size_t	width() const;
	size_t	height() const;
	std::vector<std::vector<Block*> > const & map() const;
	Block*	at(Position<int> const &) const;
	Block*	at(int, int) const;

private:
	void	loadFromFile(const std::string &);

	void	initMap();
	void	setBorders();
	void	setSolid();
	void	setDestructible();

	void	bindBlocks();
	void	replaceAt(Position<int> const &, Block*);

private:
	void	bombExploded(Subject*);
	void	blockDestroyed(Subject*);

private:
	size_t	_width;
	size_t	_height;
	std::vector<std::vector<Block*> > _map;
};

#endif	/* MAP_HPP */
