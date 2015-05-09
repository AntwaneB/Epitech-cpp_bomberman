/*
 * File:   Bomb.cpp
 * Author: buchse_a
 *
 * Created on May 7, 2015, 12:15 AM
 */

#include "global.hh"
#include "Bomb.hh"

Bomb::Bomb(Position const & position, size_t range, double duration, const Character* owner)
	: Item(position), _range(range), _duration(duration), _owner(owner), _progress(0)
{
	_actions[CLOCK_TICK] = &Bomb::tick;

	_attributes = g_settings["entities"]["bomb"];
}

Bomb::~Bomb()
{
	std::cout << "Bomb has been deleted" << std::endl;
}

bool
Bomb::hasHit(Position const & position) const
{
	return (std::find(_hitbox.begin(), _hitbox.end(), position) != _hitbox.end());
}

void
Bomb::setHitbox(std::vector<Position> const & hitbox)
{
	_hitbox = hitbox;
}

size_t
Bomb::range() const
{
	return (_range);
}

Position
Bomb::position() const
{
	return (_position);
}

void
Bomb::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);

	if (!_clockInit)
	{
		_spawnTime = clock->seconds();
		_clockInit = true;
	}
	else
	{
		seconds_t elapsed = clock->seconds() - _spawnTime;
		if (elapsed > _duration)
		{
			std::cout << "Da bomb has explodead" << std::endl;
			_progress = 100;
			this->notify(this, BOMB_EXPLODED);
		}
		else
		{
			_progress = (elapsed / _spawnTime) * 100;
			std::cout << "Da bomb is tickin' : " << (int)(_progress) << "%" << std::endl;
		}
	}
}
