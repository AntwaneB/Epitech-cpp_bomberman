/*
 * File:   BonusItem.hpp
 * Author: buchse_a
 *
 * Created on April 27, 2015, 11:11 PM
 */

#ifndef BONUSITEM_HPP
#define	BONUSITEM_HPP

#include "IEntity.hpp"
#include "Observer.hpp"

class BonusItem : public IEntity, public Observer, public Subject
{
public:
	BonusItem();
	virtual ~BonusItem();

	virtual void onNotify(IEntity const & entity, Event event);

private:

};

#endif	/* BONUSITEM_HPP */
