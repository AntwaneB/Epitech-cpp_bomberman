/*
 * File:   BonusItem.hh
 * Author: buchse_a
 *
 * Created on May 9, 2015, 12:19 PM
 */

#ifndef BONUSITEM_HH
#define	BONUSITEM_HH

#include "Observer.hpp"
#include "Item.hh"
#include "Position.hpp"

class BonusItem : public Item, public EventHandler<BonusItem>, public Subject
{
public:
	BonusItem(Position const &);
	virtual ~BonusItem();

private:
	virtual void tick(Subject*) = 0;

private:

};

#endif	/* BONUSITEM_HH */
