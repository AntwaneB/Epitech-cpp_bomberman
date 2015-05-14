/*
 * File:   BonusItem.cpp
 * Author: buchse_a
 *
 * Created on May 9, 2015, 12:19 PM
 */

#include "BonusItem.hh"

BonusItem::BonusItem(Position const & position)
	: Item(position)
{
}

BonusItem::~BonusItem()
{
}

void
BonusItem::tick(Subject* entity)
{
	(void)entity;
}
