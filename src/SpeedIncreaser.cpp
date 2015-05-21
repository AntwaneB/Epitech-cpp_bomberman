/*
 * File:   SpeedIncreaser.cpp
 * Author: buchse_a
 *
 * Created on May 21, 2015, 9:58 AM
 */

#include "Clock.hh"
#include "SpeedIncreaser.hh"

SpeedIncreaser::SpeedIncreaser(Position const & position)
	: BonusItem(position)
{
}

SpeedIncreaser::~SpeedIncreaser()
{
}

void
SpeedIncreaser::applyEffect(Character* character)
{
	(void)character;
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
