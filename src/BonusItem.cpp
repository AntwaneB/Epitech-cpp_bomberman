/*
 * File:   BonusItem.cpp
 * Author: buchse_a
 *
 * Created on May 9, 2015, 12:19 PM
 */

#include "Exception.hpp"
#include "BonusItem.hh"
#include "RangeIncreaser.hh"
#include "SpeedIncreaser.hh"
#include "BombAmountIncreaser.hh"

BonusItem::BonusItem(Position const & position, Type type)
	: Item(position, type)
{
}

BonusItem::~BonusItem()
{
}

BonusItem*
BonusItem::factory(Item::Type type, Position const & position)
{
	std::map<BonusItem::Type, BonusItem* (*)(Position const &)> _factories =
	{
		{ RANGE_INCREASER, [](Position const & position) -> BonusItem* { return (new RangeIncreaser(position)); } },
		{ SPEED_INCREASER, [](Position const & position) -> BonusItem* { return (new SpeedIncreaser(position)); } },
		{ BOMB_AMOUNT_INCREASER, [](Position const & position) -> BonusItem* { return (new BombAmountIncreaser(position)); } },
	};

	auto it = _factories.find(type);
	if (it != _factories.end())
	{
		return (((*it).second)(position));
	}
	else
		throw FactoryException("Invalid item type");

	return (NULL);
}
