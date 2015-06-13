/*
 * File:   Monster.hh
 * Author: buchse_a
 *
 * Created on June 4, 2015, 9:25 PM
 */

#ifndef MONSTER_HH
#define	MONSTER_HH

#include "Core/Level.hh"
#include "Core/Position.hh"
#include "Core/Character.hh"
#include "Core/Bomb.hh"
#include "Core/Config.hh"

class Monster : public EventHandler<Monster>, public Subject
{
	friend class	Save;

	typedef Character::Action	Action;

public:
	Monster(const Level * level, Position<double> const & position);
	Monster(const Level * level, Config::Param &);
	virtual ~Monster();

	Position<double>	position() const;
	Position<double>	prevPosition() const;
	Character::Action	direction() const;
	Config&				attributes();
	bool					alive() const;
	const Bomb*			killedBy() const;
	bool					moving() const;

private:
	void	tick(Subject* entity);
	void	bombExploded(Subject* entity);

	void	setMovement();
	void	move(Character::Action, const Clock &);

private:
	const Level*			_level;

	Position<double>		_position;
	Position<double>		_prevPosition;
	Config					_attributes;
	bool						_alive;
	const Bomb*				_killedBy;

	std::queue<Action>	_queuedActions;
	int						_elapsedTime;
	int						_elapsedCentiseconds;
	int						_prevMovement;

	bool						_moving;
	seconds_t				_movingUntil;
	Action					_direction;
};

#endif	/* MONSTER_HH */
