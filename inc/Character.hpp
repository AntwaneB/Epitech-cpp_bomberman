/*
 * File:   Character.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#ifndef CHARACTER_HPP
#define	CHARACTER_HPP

#include "Observer.hpp"

class Character : public Subject, public Observer
{
public:
	Character();
	virtual ~Character();

	virtual void onNotify(Subject* entity, Event event);

private:

};

#endif	/* CHARACTER_HPP */
