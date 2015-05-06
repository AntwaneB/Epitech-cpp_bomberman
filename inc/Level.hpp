/*
 * File:   Level.hpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include "Observer.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Item.hh"
#include <map>

class Level : public Subject, public Observer
{
public:
	Level(size_t width, size_t height, size_t charactersCount);
	virtual ~Level();

	virtual void onNotify(Subject * entity, Event event);

private:
	Map														_map;
	std::map<Position, std::list<Character*> >	_characters;
	std::map<Position, std::list<Item*> >			_items;
};

#endif	/* LEVEL_HPP */
