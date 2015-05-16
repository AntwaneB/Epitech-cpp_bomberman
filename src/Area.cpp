#include "Area.hh"

Area::Area(bool destructible, bool visible, bool solid, bool blockBombs)
{
	_destructible = destructible;
	_free = visible;
	_wall = solid;
	_bomb = blockBombs;
	_direction = Character::WAIT;
	_enemy = 0;
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

bool Area::free() const
{
	return _free;
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

void Area::decEnemy()
{
	_enemy -= 1;
}

void Area::setFree(bool value)
{
	_free = value;
}

void Area::setDirection(Character::Action move)
{
	_direction = move;
}