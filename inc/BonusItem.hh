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
#include "Character.hpp"

class BonusItem : public Item, public EventHandler<BonusItem>, public Subject
{
public:
	BonusItem(Position const &);
	virtual ~BonusItem();

	virtual void applyEffect(Character*) = 0;

	static BonusItem* factory(BonusItem::Type type, Position const &);

private:
	virtual void tick(Subject*) = 0;

private:

};

#endif	/* BONUSITEM_HH */
