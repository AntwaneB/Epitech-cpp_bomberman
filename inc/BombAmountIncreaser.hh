/*
 * File:   BombAmountIncreaser.hh
 * Author: buchse_a
 *
 * Created on May 21, 2015, 9:59 AM
 */

#ifndef BOMBAMOUNTINCREASER_HH
#define	BOMBAMOUNTINCREASER_HH

#include "BonusItem.hh"
#include "Character.hpp"

class BombAmountIncreaser : public BonusItem
{
public:
	BombAmountIncreaser(Position const &);
	virtual ~BombAmountIncreaser();

	virtual void applyEffect(Character*);

private:
	virtual void tick(Subject*);

private:

};

#endif	/* BOMBAMOUNTINCREASER_HH */
