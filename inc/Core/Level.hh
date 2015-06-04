/*
 * File:   Level.hpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#ifndef LEVEL_HPP
#define	LEVEL_HPP

class Monster;

#include <map>
#include "Core/Observer.hpp"
#include "Core/Clock.hh"
#include "Core/Position.hh"
#include "Core/Map.hh"
#include "Core/Character.hh"
#include "Core/Item.hh"
#include "Core/BonusItem.hh"
#include "Core/Bomb.hh"

class Level : public EventHandler<Level>, public Subject
{
	friend class	Save;

public:
	Level(size_t width, size_t height, size_t charactersCount, size_t playersCount, IA::Difficulty);
	virtual ~Level();

	void				run();
	Clock&			clock();

	Map const &		map() const;
	size_t			charactersCount() const;

	std::map<Position<>, std::list<Character*> > const &
	characters() const;
	std::map<Position<>, std::list<Bomb*> > const &
	bombs() const;
	std::map<Position<>, std::list<Item*> > const &
	items() const;
	std::map<Position<>, std::list<Monster*> > const &
	monsters() const;
	std::list<Character*> const &	players() const;
	std::vector<Character*> const	charactersRaw() const;
	std::vector<Bomb*> const		bombsRaw() const;
	std::vector<BonusItem*>	const	itemsRaw() const;
	std::vector<Monster*>	const	monstersRaw() const;
	std::list<Bomb::Explosion>		explosions() const;

private:
	Character*	pushCharacter();
	Monster*		pushMonster();
	void			end();

	void	characterMoved(Subject* entity);
	void	characterDied(Subject* entity);
	void	monsterMoved(Subject* entity);
	void	monsterDied(Subject* entity);
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
	Map														_map;
	std::map<Position<>, std::list<Character*> >	_characters;
	std::list<Character*>								_players;
	std::map<Position<>, std::list<Bomb*> >		_bombs;
	std::map<Position<>, std::list<BonusItem*> >	_items;
	std::list<Bomb::Explosion>							_explosions;
	std::map<Position<>, std::list<Monster*> >	_monsters;

	size_t													_charactersCount;
	size_t													_playersCount;
	Clock														_clock;
	size_t													_secondsElapsed;

	std::list<Character*>								_scores;
	size_t													_charactersKills;

	IA::Difficulty											_difficulty;
};

#endif	/* LEVEL_HPP */
