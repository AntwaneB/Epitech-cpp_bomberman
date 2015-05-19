#include "IA.hpp"

IA::Area::Area(bool destructible, bool solid)
{
	_destructible = destructible;
	_wall = solid;
	_direction = Character::WAIT;
	_enemy = 0;
	_history = 0;
}

IA::Area::Area()
{

}

IA::Area::~Area()
{

}

bool IA::Area::explosion() const
{
	return _explosion;
}

bool IA::Area::bomb() const
{
	return _bomb;
}

int IA::Area::enemy() const
{
	return _enemy;
}

int IA::Area::history() const
{
	return _history;
}

bool IA::Area::wall() const
{
	return _wall;
}

bool IA::Area::destructible() const
{
	return _destructible;
}

Character::Action IA::Area::direction() const
{
	return _direction;
}

void IA::Area::setExplosion(bool value)
{
	_explosion = value;
}

void IA::Area::setBomb(bool value)
{
	_bomb = value;
}

void IA::Area::incEnemy()
{
	_enemy += 1;
}

void IA::Area::incHistory()
{
	_history += 1;
}

void IA::Area::setDirection(Character::Action move)
{
	_direction = move;
}
