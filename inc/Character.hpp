/*
 * File:   Character.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#ifndef CHARACTER_HPP
#define	CHARACTER_HPP

#include "Observer.hpp"
#include "Position.hpp"

class Character : public Subject, public Observer
{
public:
	Character(size_t nth, size_t x, size_t y, size_t z = 0);
	virtual ~Character();

	virtual void onNotify(Subject* entity, Event event);

private:
	size_t	_nth;
	Position	_position;
};

#endif	/* CHARACTER_HPP */
