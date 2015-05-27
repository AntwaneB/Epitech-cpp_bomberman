/*
 * File:   SpeedIncreaser.hh
 * Author: buchse_a
 *
 * Created on May 21, 2015, 9:58 AM
 */

#ifndef SPEEDINCREASER_HH
#define	SPEEDINCREASER_HH

#include "BonusItem.hh"
#include "Character.hh"

class SpeedIncreaser : public BonusItem
{
public:
	SpeedIncreaser(Position<> const &);
	virtual ~SpeedIncreaser();

	virtual void applyEffect(Character*);

private:
	virtual void tick(Subject*);

private:

};

#endif	/* SPEEDINCREASER_HH */
