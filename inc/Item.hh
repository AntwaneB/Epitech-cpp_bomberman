/*
 * File:   Item.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:30 PM
 */

#ifndef ITEM_HH
#define	ITEM_HH

#include "Observer.hpp"
#include "Position.hpp"
#include "Clock.hpp"

class Item
{
public:
	Item(Position const &);
	virtual ~Item() = 0;

	Position	position() const;
	Position	prevPosition() const;
	void		toConfig(Config &) const;

private:
	virtual void tick(Subject*) = 0;

protected:
	Position		_position;
	Position		_prevPosition;

	bool			_clockInit;
	seconds_t	_spawnTime;
};

#endif	/* ITEM_HH */
