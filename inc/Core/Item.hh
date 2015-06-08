/*
 * File:   Item.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:30 PM
 */

#ifndef ITEM_HH
#define	ITEM_HH

#include "Observer.hpp"
#include "Position.hh"
#include "Clock.hh"
#include "Character.hh"

class Item
{
	friend class	Save;

public:
	enum Type { RANGE_INCREASER, SPEED_INCREASER, BOMB_AMOUNT_INCREASER, last };

public:
	Item(Position<> const &, Type type = last);
	Item(Config::Param);
	virtual ~Item() = 0;

	Type		type() const;
	Position<>	position() const;
	Position<>	prevPosition() const;
	void		toConfig(Config::Param &) const;

protected:
	Position<>		_position;
	Position<>		_prevPosition;
	Type			_type;

	bool			_clockInit;
	seconds_t	_spawnTime;
};

#endif	/* ITEM_HH */
