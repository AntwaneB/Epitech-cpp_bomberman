/*
 * File:   RangeIncreaser.hh
 * Author: buchse_a
 *
 * Created on May 14, 2015, 4:44 PM
 */

#ifndef RANGEINCREASER_HH
#define	RANGEINCREASER_HH

#include "BonusItem.hh"
#include "Character.hpp"

class RangeIncreaser : public BonusItem
{
public:
	RangeIncreaser(Position const &);
	virtual ~RangeIncreaser();

	virtual void applyEffect(Character*);

private:
	virtual void tick(Subject*);

private:

};

#endif	/* RANGEINCREASER_HH */
