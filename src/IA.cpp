#include "IA.hpp"

Area::Area(bool destructible, bool solid)
{
	_destructible = destructible;
	_wall = solid;
	_direction = Character::WAIT;
	_enemy = 0;
}

Area::Area()
{

}

Area::~Area()
{

}

bool Area::explosion() const
{
	return _explosion;
}

bool Area::bomb() const
{
	return _bomb;
}

int Area::enemy() const
{
	return _enemy;
}

bool Area::wall() const
{
	return _wall;
}

bool Area::destructible() const
{
	return _destructible;
}

Character::Action Area::direction() const
{
	return _direction;
}

void Area::setExplosion(bool value)
{
	_explosion = value;
}

void Area::setBomb(bool value)
{
	_bomb = value;
}

void Area::incEnemy()
{
	_enemy += 1;
}

void Area::setDirection(Character::Action move)
{
	_direction = move;
}
