/*
 * File:   Character.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#ifndef CHARACTER_HPP
#define	CHARACTER_HPP

#include <queue>
#include <list>
#include "Observer.hpp"
#include "Position.hpp"
#include "Bomb.hh"
#include "Config.hpp"

class Character : public EventHandler<Character>, public Subject
{
public:
	enum Action { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, DROP_BOMB, WAIT };

public:
	Character(size_t nth, size_t x, size_t y, size_t z = 0);
	virtual ~Character();

	Position	position() const;
	Position	prevPosition() const;

	void		toConfig(Config &) const;

private:
	void tick(Subject* entity);
	void bombExploded(Subject* entity);

	void move(Action);
	void dropBomb();

private:
	size_t					_nth;
	Position					_position;
	Position					_prevPosition;
	Config					_attributes;
	std::list<Bomb*>		_bombs;
	std::queue<Action>	_queuedActions;

	int						_elapsedTime;
};

#endif	/* CHARACTER_HPP */
