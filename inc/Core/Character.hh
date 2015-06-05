/*
 * File:   Character.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#ifndef CHARACTER_HPP
#define	CHARACTER_HPP

class Level;
class Bomb;
namespace IA
{
	enum Difficulty { EASY = 1, MEDIUM = 2, HARD = 3 };

	template<Difficulty T>
	class IA;
};

#include <queue>
#include <list>
#include "Core/Observer.hpp"
#include "Core/Position.hh"
#include "Core/Clock.hh"
#include "Config.hh"

class Character : public EventHandler<Character>, public Subject
{
	friend class	Save;

public:
	enum Action { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, DROP_BOMB, WAIT };

public:
	Character(const Level * level, size_t nth, bool isPlayer, IA::Difficulty, size_t x, size_t y, size_t z = 0);
	Character(Config::Param);
	virtual ~Character();

	Position<double>	position() const;
	Position<double>	prevPosition() const;
	Character::Action	direction() const;
	Config&				attributes();
	bool					alive() const;
	int					score() const;
	void					changeScore(int);
	const Bomb*			killedBy() const;
	bool					isPlayer() const;
	bool					moving() const;

	void		clearActions();
	void		pushAction(Character::Action);

private:
	void tick(Subject* entity);
	void bombExploded(Subject* entity);
	void keyPressed(Subject* entity);

	void move(Action, const Clock &);
	void dropBomb();

private:
	const Level*			_level;
	size_t					_nth;
	bool						_isPlayer;
	Position<double>		_position;
	Position<double>		_prevPosition;
	Config					_attributes;
	bool						_solid;
	bool						_alive;
	const Bomb*				_killedBy;

	IA::IA<IA::HARD>*		_iaHard;
	IA::IA<IA::MEDIUM>*	_iaMedium;
	IA::IA<IA::EASY>*		_iaEasy;

	std::list<Bomb*>		_bombs;
	std::queue<Action>	_queuedActions;
	seconds_t				_previousBomb;
	int						_elapsedTime;
	int						_elapsedCentiseconds;
	int						_prevMovement;

	bool						_moving;
	seconds_t				_movingUntil;
	Action					_direction;

	int						_score;
};

#endif	/* CHARACTER_HPP */
