/*
 * File:   RangeIncreaser.cpp
 * Author: buchse_a
 *
 * Created on May 14, 2015, 4:44 PM
 */

#include "RangeIncreaser.hh"
#include "Clock.hpp"

RangeIncreaser::RangeIncreaser(Position const & position)
	: BonusItem(position)
{
}

RangeIncreaser::~RangeIncreaser()
{
}

void
RangeIncreaser::applyEffect(Character* character)
{
	(void)character;
}

void
RangeIncreaser::tick(Subject* entity)
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
