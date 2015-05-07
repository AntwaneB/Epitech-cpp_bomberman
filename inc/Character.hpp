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
#include "Config.hpp"

class Character : public EventHandler<Character>, public Subject
{
public:
	Character(size_t nth, size_t x, size_t y, size_t z = 0);
	virtual ~Character();

	Position	position() const;
	Position	prevPosition() const;

private:
	void move();

private:
	size_t	_nth;
	Position	_position;
	Position	_prevPosition;
	Config	_attributes;
};

#endif	/* CHARACTER_HPP */
