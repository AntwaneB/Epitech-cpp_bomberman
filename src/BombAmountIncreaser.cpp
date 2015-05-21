/*
 * File:   BombAmountIncreaser.cpp
 * Author: buchse_a
 *
 * Created on May 21, 2015, 9:59 AM
 */

#include "BombAmountIncreaser.hh"
#include "Clock.hpp"

BombAmountIncreaser::BombAmountIncreaser(Position const & position)
	: BonusItem(position)
{
}

BombAmountIncreaser::~BombAmountIncreaser()
{
}

void
BombAmountIncreaser::applyEffect(Character* character)
{
	(void)character;
}

void
BombAmountIncreaser::tick(Subject* entity)
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
