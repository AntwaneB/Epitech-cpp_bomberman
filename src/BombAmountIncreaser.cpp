/*
 * File:   BombAmountIncreaser.cpp
 * Author: buchse_a
 *
 * Created on May 21, 2015, 9:59 AM
 */

#include "global.hh"
#include "Core/BombAmountIncreaser.hh"
#include "Core/Clock.hpp"

BombAmountIncreaser::BombAmountIncreaser(Position const & position)
	: BonusItem(position, Item::BOMB_AMOUNT_INCREASER)
{
	_attributes = g_settings["entities"]["bonus_item"]["bomb_amount_increase"];
}

BombAmountIncreaser::~BombAmountIncreaser()
{
}

void
BombAmountIncreaser::applyEffect(Character* character)
{
	int bombAmount = character->attributes()["bombs"]["amount"];
	bombAmount += static_cast<int>(_attributes["bomb_amount_modifier"]);
	bombAmount = bombAmount < 0 ? 0 : bombAmount;

	character->attributes()["bombs"]["amount"] = bombAmount;

	this->notify(this, ITEM_DESTROYED);
	delete this;
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
