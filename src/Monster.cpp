/*
 * File:   Monster.cpp
 * Author: buchse_a
 *
 * Created on June 4, 2015, 9:25 PM
 */

#include "global.hh"
#include "Core/Monster.hh"

Monster::Monster(const Level * level, Position<double> const & position)
	: _level(level), _position(position), _alive(true), _killedBy(NULL), _elapsedTime(-1),
	  _elapsedCentiseconds(-1), _prevMovement(-1), _moving(false), _direction(Character::MOVE_DOWN)
{
	_actions[CLOCK_TICK] = &Monster::tick;
	_actions[LEVEL_BOMB_EXPLODED] = &Monster::bombExploded;

	_attributes = g_settings["entities"]["monster"];

	this->notify(this, MONSTER_SPAWNED);
}

Monster::Monster(const Level * level, Config::Param cfg)
	: _level(level), _position(cfg["position"]),  _prevPosition(cfg["prevPosition"]), _alive(cfg["alive"]), _killedBy(NULL), _elapsedTime(cfg["elapsedTime"]),
	_elapsedCentiseconds(-1), _prevMovement(-1), _moving(false), _direction(Character::MOVE_DOWN)
{
	_actions[CLOCK_TICK] = &Monster::tick;
	_actions[LEVEL_BOMB_EXPLODED] = &Monster::bombExploded;

	_attributes = cfg["attributes"];
}

Monster::~Monster()
{
}

Position<double>
Monster::position() const
{
	return (_position);
}

Position<double>
Monster::prevPosition() const
{
	return (_prevPosition);
}

Config&
Monster::attributes()
{
	return (_attributes);
}

bool
Monster::alive() const
{
	return (_alive);
}

const Bomb*
Monster::killedBy() const
{
	return (_killedBy);
}

bool
Monster::moving() const
{
	return (_moving);
}

Character::Action
Monster::direction() const
{
	return (_direction);
}

void
Monster::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);

	if (_elapsedTime == -1)
		_elapsedTime = clock->deciseconds();
	if (_elapsedCentiseconds == -1)
		_elapsedCentiseconds = clock->centiseconds();

	// Capping speed
	if (_attributes["speed"] > static_cast<int>(_attributes["max_speed"]))
		_attributes["speed"] = static_cast<int>(_attributes["max_speed"]);

	// Managing animations
	if (_moving && clock->seconds() >= _movingUntil)
	{
		_moving = false;
	}

	// Updating clocks & running IA
	if (static_cast<int>(clock->deciseconds()) - _elapsedTime >= 1)
	{
		_elapsedTime++;

		this->setMovement();
	}
	if (static_cast<int>(clock->centiseconds()) - _elapsedCentiseconds >= 1)
	{
		_elapsedCentiseconds += static_cast<int>(clock->centiseconds()) - _elapsedCentiseconds;
	}

	// Managing actions
	if (_queuedActions.size() > 0
		&& (_queuedActions.front() == Character::MOVE_UP || _queuedActions.front() == Character::MOVE_DOWN
		 || _queuedActions.front() == Character::MOVE_LEFT || _queuedActions.front() == Character::MOVE_RIGHT)
		&& _attributes["can_move"] == true
		&& _attributes["speed"] != 0
		&& _elapsedCentiseconds / (static_cast<int>(_attributes["max_speed"]) / static_cast<int>(_attributes["speed"])) > _prevMovement)
	{ // Triggering movement
		_prevMovement = _elapsedCentiseconds / (static_cast<int>(_attributes["max_speed"]) / static_cast<int>(_attributes["speed"]));
		Character::Action movement = _queuedActions.front();
		_queuedActions.pop();

		this->move(movement, *clock);
	}

}

void
Monster::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	if (bomb->hasHit(_position.asInt()))
	{ // The character got hit by the bomb
		_alive = false;
		_killedBy = bomb;
		this->notify(this, MONSTER_DIED);
	}
}

void
Monster::setMovement()
{
	if (_queuedActions.empty())
	{
		Action direction;
		int i = 0;
		while ((direction = static_cast<Action>(rand() % Character::end_move)) != _direction && ++i < 5);

		for (i = 0; i < 10; i++)
			_queuedActions.push(direction);
	}
}

void
Monster::move(Character::Action action, const Clock & clock)
{
	Position<double> newPos = _position;

	double step = 0.001 * static_cast<int>(_attributes["speed"]) + 0.01;

	double duration = 0.0 / 1000.0;

	switch (action)
	{
		case Character::MOVE_DOWN:
			newPos.incY(step);
			break;
		case Character::MOVE_UP:
			newPos.decY(step);
			break;
		case Character::MOVE_LEFT:
			newPos.decX(step);
			break;
		case Character::MOVE_RIGHT:
			newPos.incX(step);
			break;
		default:
			break;
	}

	if (newPos.outOfBounds(_level->map().width() - 1, _level->map().height() - 1) || newPos.x() < 1 || newPos.y() < 1)
	{
		while (!_queuedActions.empty())
			_queuedActions.pop();
	}
	else
	{
		_prevPosition = _position;
		switch (action)
		{
			case Character::MOVE_DOWN:
				_position.incY(step);
				break;
			case Character::MOVE_UP:
				_position.decY(step);
				break;
			case Character::MOVE_LEFT:
				_position.decX(step);
				break;
			case Character::MOVE_RIGHT:
				_position.incX(step);
				break;
			default:
				break;
		}

		_moving = true;
		_movingUntil = clock.seconds() + duration * 2;
		_direction = action;

		this->notify(this, MONSTER_MOVED);
	}
}
