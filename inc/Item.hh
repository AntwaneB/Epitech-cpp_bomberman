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

class Item : public EventHandler<Item>, public Subject
{
public:
	Item();
	virtual ~Item();

	Position	position() const;
	Position	prevPosition() const;

private:
	Position	_position;
	Position	_prevPosition;
};

#endif	/* ITEM_HH */
