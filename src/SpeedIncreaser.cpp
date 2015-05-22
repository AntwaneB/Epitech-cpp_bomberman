/*
 * File:   SpeedIncreaser.cpp
 * Author: buchse_a
 *
 * Created on May 21, 2015, 9:58 AM
 */

#include "global.hh"
#include "Clock.hh"
#include "SpeedIncreaser.hh"

SpeedIncreaser::SpeedIncreaser(Position const & position)
	: BonusItem(position, Item::SPEED_INCREASER)
{
	_attributes = g_settings["entities"]["bonus_item"]["speed_increase"];
}

SpeedIncreaser::~SpeedIncreaser()
{
}

void
SpeedIncreaser::applyEffect(Character* character)
{
	int speed = character->attributes()["speed"];
	speed += static_cast<int>(_attributes["speed_modifier"]);
	speed = speed < 0 ? 0 : speed;

	character->attributes()["speed"] = speed;

	this->notify(this, ITEM_DESTROYED);
	delete this;
}

void
SpeedIncreaser::tick(Subject* entity)
{
	Clock* clock = safe_cast<Clock*>(entity);

	if (!_clockInit)
	{
		_spawnTime = clock->seconds();
		_clockInit = true;
	}
	else
	{
	}
}
