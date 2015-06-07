/*
 * File:   Bomb.cpp
 * Author: buchse_a
 *
 * Created on May 7, 2015, 12:15 AM
 */

#include "global.hh"
#include "Core/Bomb.hh"

Bomb::Bomb(Position<> const & position, size_t range, double duration, const Character* owner)
	: Item(position), _range(range), _duration(duration), _owner(owner), _progress(0)
{
	_actions[CLOCK_TICK] = &Bomb::tick;

	_attributes = g_settings["entities"]["bomb"];
}

Bomb::Bomb(Config::Param cfg) : Item(Position<>(cfg["position"]))
{
	_range = cfg["range"];
	_attributes = cfg["attributes"];
	_owner = NULL;
}

Bomb::~Bomb()
{
}

bool
Bomb::hasHit(Position<> const & position) const
{
	return (std::find(_hitbox.begin(), _hitbox.end(), position) != _hitbox.end());
}

void
Bomb::setHitbox(std::vector<Position<> > const & hitbox)
{
	_hitbox = hitbox;
}

size_t
Bomb::range() const
{
	return (_range);
}

char
Bomb::progress() const
{
	return (_progress);
}

const Character*
Bomb::owner() const
{
	return (_owner);
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
			_progress = 100;
			this->notify(this, BOMB_EXPLODED);
			delete this;
		}
		else
		{
			_progress = (elapsed / _duration) * 100;
		}
	}
}
/*
void
Bomb::toConfig(Config & cfg) const
{
	cfg["attributes"] = _attributes;
	cfg["range"] = _range;
	cfg["duration"] = _duration;
	cfg["progress"] = progress;
}
*/