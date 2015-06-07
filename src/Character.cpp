/*
 * File:   Character.cpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#include <iostream>
#include "global.hh"
#include "Core/Character.hh"
#include "Exception.hpp"
#include "Core/Clock.hh"
#include "Core/Level.hh"
#include "Core/IA.hpp"
#include "Core/Input.hh"

Character::Character(const Level * level, size_t id, bool isPlayer, IA::Difficulty difficulty, size_t x, size_t y, size_t z)
	: _level(level), _id(id), _isPlayer(isPlayer), _position(x + 0.5, y + 0.5, z), _solid(true), _alive(true),
	  _killedBy(NULL), _iaHard(NULL), _iaMedium(NULL), _iaEasy(NULL), _previousBomb(-1), _elapsedTime(-1),
	  _elapsedCentiseconds(-1), _prevMovement(-1), _moving(false), _direction(MOVE_DOWN), _score(0)
{
	_actions[CLOCK_TICK] = &Character::tick;
	_actions[LEVEL_BOMB_EXPLODED] = &Character::bombExploded;
	_actions[KEY_PRESSED] = &Character::keyPressed;

	_attributes = g_settings["entities"]["character"];

	if (!_isPlayer)
	{
		switch (difficulty)
		{
			case IA::HARD:
				_iaHard = new IA::IA<IA::HARD>(_level, this);
			case IA::MEDIUM:
				_iaMedium = new IA::IA<IA::MEDIUM>(_level, this);
			default:
				_iaEasy = new IA::IA<IA::EASY>(_level, this);
		}
	}

	this->notify(this, CHARACTER_SPAWNED);
}

Character::Character(const Level * level, Config::Param cfg)
	: _level(level), _position(cfg["position"]), _prevPosition(cfg["prevPosition"]), _killedBy(NULL),
	  _iaHard(NULL), _iaMedium(NULL), _iaEasy(NULL), _previousBomb(0), _prevMovement(-1), _moving(false),
	  _direction(MOVE_DOWN)
{
	_actions[CLOCK_TICK] = &Character::tick;
	_actions[LEVEL_BOMB_EXPLODED] = &Character::bombExploded;
	_actions[KEY_PRESSED] = &Character::keyPressed;

	_id = cfg["id"];
	_isPlayer = cfg["isPlayer"];
	_attributes = cfg["attributes"];
	_solid = true;
	_alive = cfg["alive"];
	_elapsedTime = cfg["elapsedTime"];
	_elapsedCentiseconds = _elapsedTime * 10;
	_score = cfg["score"];
	if (!_isPlayer)
	{
		switch (cfg["ia"])
		{
			case "hard":
				_iaHard = new IA::IA<IA::HARD>(_level, this);
			case "medium":
				_iaMedium = new IA::IA<IA::MEDIUM>(_level, this);
			case "easy":
				_iaEasy = new IA::IA<IA::EASY>(_level, this);
		}
	}

}

Character::~Character()
{
	if (_iaHard)
		delete _iaHard;
	if (_iaMedium)
		delete _iaMedium;
	if (_iaEasy)
		delete _iaEasy;
}

Position<double>
Character::position() const
{
	return (_position);
}

Position<double>
Character::prevPosition() const
{
	return (_prevPosition);
}

Config&
Character::attributes()
{
	return (_attributes);
}

bool
Character::alive() const
{
	return (_alive);
}

int
Character::score() const
{
	return (_score);
}

void
Character::changeScore(int amount)
{
	_score += amount;
}

const Bomb*
Character::killedBy() const
{
	return (_killedBy);
}

bool
Character::isPlayer() const
{
	return (_isPlayer);
}

bool
Character::moving() const
{
	return (_moving);
}

Character::Action
Character::direction() const
{
	return (_direction);
}

void
Character::tick(Subject* entity)
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

		if ((_iaHard || _iaMedium || _iaEasy) && !_isPlayer)
		{
			if (_iaHard != NULL)
				_iaHard->playTurn();
			else if (_iaMedium)
				_iaMedium->playTurn();
			else
				_iaEasy->playTurn();
		}
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

	if (_queuedActions.size() > 0 && _queuedActions.front() == Character::DROP_BOMB)
	{ // Dropping a bomb
		_queuedActions.pop();

		if (_attributes["bombs"]["available"] == true
			&& _bombs.size() < static_cast<size_t>(_attributes["bombs"]["amount"])
			&& clock->seconds() - _previousBomb > 0.2)
		{
			_previousBomb = clock->seconds();
			this->dropBomb();
		}
	}

}

void
Character::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	auto it = std::find(_bombs.begin(), _bombs.end(), bomb);
	if (it != _bombs.end())
		_bombs.erase(it);

	if (bomb->hasHit(_position))
	{ // The character got hit by the bomb
		_alive = false;
		_killedBy = bomb;
		this->notify(this, CHARACTER_DIED);
//		delete this;
	}
}

void
Character::keyPressed(Subject* entity)
{
	Input* input = safe_cast<Input*>(entity);

	std::map<Input::Key, Character::Action> keys;
	keys[Input::UP] = Character::MOVE_UP;
	keys[Input::DOWN] = Character::MOVE_DOWN;
	keys[Input::RIGHT] = Character::MOVE_RIGHT;
	keys[Input::LEFT] = Character::MOVE_LEFT;
	keys[Input::SPACE] = Character::DROP_BOMB;

	if (input->genericKey() > Input::KEYS_GENERIC_START && input->genericKey() < Input::KEYS_GENERIC_END)
	{
		this->clearActions();
		this->pushAction(keys[input->genericKey()]);
	}
}

void
Character::move(Character::Action action, const Clock & clock)
{
	Position<double> newPos = _position;

	double step = 0.001 * static_cast<int>(_attributes["speed"]);

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
		return;

	Position<double> newPosRightDown(newPos);
	newPosRightDown.incX(0.25);
	newPosRightDown.incY(0.25);
	Position<double> newPosLeftUp(newPos);
	newPosLeftUp.decX(0.25);
	newPosLeftUp.decY(0.25);
	Position<double> newPosLeftDown(newPos);
	newPosLeftDown.decX(0.25);
	newPosLeftDown.incY(0.25);
	Position<double> newPosRightUp(newPos);
	newPosRightUp.incX(0.25);
	newPosRightUp.decY(0.25);

	auto bombs = _level->bombs();
	if ((_level->map().at(newPosLeftUp)->solid() == false && _level->map().at(newPosRightDown)->solid() == false
		 && _level->map().at(newPosLeftDown)->solid() == false && _level->map().at(newPosRightUp)->solid() == false
		 && (bombs[newPos].empty() || (!bombs[_position].empty() && (bombs[newPos].empty() || newPos.asInt() == _position.asInt()))))
		|| _solid == false)
	{ // The block where we want to move isn't solid and their's no bomb there

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

		this->notify(this, CHARACTER_MOVED);
	}
}

void
Character::dropBomb()
{
	size_t range = _attributes["bombs"]["range"];
	double duration = g_settings["entities"]["bomb"]["duration"];
	double duration_modifier = _attributes["bombs"]["duration_modifier"];

	Bomb* bomb = new Bomb(_position, range, duration * duration_modifier, this);

	_bombs.push_back(bomb);

	this->notify(bomb, BOMB_DROPPED);
}

void
Character::pushAction(Character::Action action)
{
	clearActions();
	_queuedActions.push(action);
}

void
Character::clearActions()
{
	while (!_queuedActions.empty())
		_queuedActions.pop();
}
