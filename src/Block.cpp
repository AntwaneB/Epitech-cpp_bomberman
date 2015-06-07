/*
 * File:   Block.cpp
 * Author: buchse_a
 *
 * Created on May 11, 2015, 11:27 AM
 */

#include "global.hh"
#include "Core/Block.hh"
#include "Core/Bomb.hh"

Block::Block(Position<> const & position, std::string const & type)
	: _position(position), _type(type), _elapsedTime(0)
{
	_actions[CLOCK_TICK] = &Block::tick;
	_actions[MAP_BOMB_EXPLODED] = &Block::bombExploded;

	_attributes = g_settings["entities"]["blocks"][_type];
	_visible = g_settings["entities"]["blocks"][_type]["visible"];
	_destructible = g_settings["entities"]["blocks"][_type]["destructible"];
	_solid = g_settings["entities"]["blocks"][_type]["collision"];
	_blockBombs = g_settings["entities"]["blocks"][_type]["block_bombs"];
	_texture = static_cast<std::string>(g_settings["entities"]["blocks"][_type]["texture"]);
}

Block::Block(Config::Param cfg) : _position(cfg["position"])
{
	_type = static_cast<std::string>(cfg["type"]);
	_attributes = cfg["attributes"];
	_elapsedTime = cfg["elapsedTime"];
	_visible = cfg["visible"];
	_destructible = cfg["destructible"];
	_solid = cfg["solid"];
	_blockBombs = cfg["blockBombs"];
	_texture = static_cast<std::string>(cfg["texture"]);
	std::cout << _position.x() << std::endl;
}

Block::~Block()
{
}

Position<>
Block::position() const
{
	return (_position);
}

bool
Block::destructible() const
{
	return (_destructible);
}

bool
Block::visible() const
{
	return (_visible);
}

bool
Block::solid() const
{
	return (_solid);
}

bool
Block::blockBombs() const
{
	return (_blockBombs);
}

std::string
Block::texture() const
{
	return (_texture);
}

void
Block::bombExploded(Subject* entity)
{
	Bomb* bomb = safe_cast<Bomb*>(entity);

	if (destructible() && bomb->hasHit(_position))
	{ // The block got hit by the bomb and is destructible
		this->notify(this, BLOCK_DESTROYED);
		delete this;
	}
}

void
Block::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);

	(void)clock;
}

void
Block::setBlockBombs(bool value)
{
	_blockBombs = value;
}

void
Block::setVisible(bool value)
{
	_visible = value;
}
