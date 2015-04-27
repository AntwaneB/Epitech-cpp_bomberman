/*
 * File:   Character.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 10:53 PM
 */

#ifndef CHARACTER_HPP
#define	CHARACTER_HPP

#include "IEntity.hpp"
#include "Observer.hpp"

class Character : public IEntity, public Observer, public Subject
{
public:
	Character();
	virtual ~Character();

	virtual void onNotify(IEntity const & entity, Event event);

private:

};

#endif	/* CHARACTER_HPP */
