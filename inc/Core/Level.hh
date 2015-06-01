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
#include "Clock.hh"
#include "Position.hh"
#include "Map.hh"
#include "Character.hh"
#include "Item.hh"
#include "BonusItem.hh"
#include "Bomb.hh"
#include "Level.hh"

class Level : public EventHandler<Level>, public Subject
{
public:
	Level(size_t width, size_t height, size_t charactersCount, size_t playersCount);
	virtual ~Level();

	void				run();
	Clock&			clock();

	Map const &		map() const;
	size_t			charactersCount() const;

	std::map<Position<>, std::list<Character*> > const &	characters() const;
	std::map<Position<>, std::list<Bomb*> > const &		bombs() const;
	std::map<Position<>, std::list<Item*> > const &		items() const;
	std::list<Character*> const &						players() const;
	std::vector<Character*> const charactersRaw() const;
	std::vector<Bomb*>		const bombsRaw() const;
	std::vector<BonusItem*>	const itemsRaw() const;

	void	exportFile(const std::string &) const;
	void	toConfig(Config & cfg) const;

private:
	Character*	pushCharacter();
	void			end();

	void	characterMoved(Subject* entity);
	void	characterDied(Subject* entity);
	void	itemDropped(Subject* entity);
	void	itemMoved(Subject* entity);
	void	itemDestroyed(Subject* entity);
	void	bombDropped(Subject* entity);
	void	bombExploded(Subject* entity);
	void	blockDestroyed(Subject* entity);
	void	keyPressed(Subject* entity);
	void	quitLevel(Subject* entity);

	void	tick(Subject* entity);
	void	pauseTick(Subject* entity);

private:
	void	charactersToConfig(Config &) const;

	private:
	Map														_map;
	std::map<Position<>, std::list<Character*> >	_characters;
	std::list<Character*>								_players;
	std::map<Position<>, std::list<Bomb*> >		_bombs;
	std::map<Position<>, std::list<BonusItem*> >	_items;
	std::list<std::pair<seconds_t, std::vector<Position<> > > >	_explosions;

	size_t													_charactersCount;
	size_t													_playersCount;
	Clock														_clock;
	size_t													_secondsElapsed;

	std::list<Character*>								_scores;
	size_t													_charactersKills;
};

#endif	/* LEVEL_HPP */
