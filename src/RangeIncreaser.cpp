/*
 * File:   RangeIncreaser.cpp
 * Author: buchse_a
 *
 * Created on May 14, 2015, 4:44 PM
 */

#include "global.hh"
#include "RangeIncreaser.hh"
#include "Clock.hpp"

RangeIncreaser::RangeIncreaser(Position const & position)
	: BonusItem(position, Item::RANGE_INCREASER)
{
	_attributes = g_settings["entities"]["bonus_item"]["range_increase"];
}

RangeIncreaser::~RangeIncreaser()
{
}

void
RangeIncreaser::applyEffect(Character* character)
{
	int range = character->attributes()["bombs"]["range"];
	range += static_cast<int>(_attributes["range_modifier"]);
	range = range < 0 ? 0 : range;

	character->attributes()["bombs"]["range"] = range;

	this->notify(this, ITEM_DESTROYED);
	delete this;
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
