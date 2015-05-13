/*
 * File:   Level.hpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include <map>
#include "Observer.hpp"
#include "Clock.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Item.hh"
#include "BonusItem.hh"
#include "Bomb.hh"

class Level : public EventHandler<Level>, public Subject
{
public:
	Level(size_t width, size_t height, size_t charactersCount);
	virtual ~Level();

	void				run();
	Clock&			clock();

	Map const &		map() const;
	size_t			charactersCount() const;
	std::map<Position, std::list<Character*> > const & characters() const;
	std::map<Position, std::list<Bomb*> > const & bombs() const;
	std::map<Position, std::list<Item*> > const & items() const;

	void	exportFile(const std::string &) const;
	void	toConfig(Config & cfg) const;

private:
	Character*	pushCharacter();

	void	characterMoved(Subject* entity);
	void	characterDied(Subject* entity);
	void	itemDropped(Subject* entity);
	void	itemMoved(Subject* entity);
	void	bombDropped(Subject* entity);
	void	bombExploded(Subject* entity);

	void	charactersToConfig(Config &) const;
	void	tick(Subject* entity);

private:
	Map														_map;
	std::map<Position, std::list<Character*> >	_characters;
	std::map<Position, std::list<Bomb*> >			_bombs;
	std::map<Position, std::list<Item*> >			_items;

	size_t													_charactersCount;
	Clock														_clock;
};

#endif	/* LEVEL_HPP */
