/*
 * File:   Level.hpp
 * Author: buchse_a
 *
 * Created on May 4, 2015, 2:34 PM
 */

#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include "Observer.hpp"

class Level : public Observer
{
public:
	Level();
	Level(const Level& orig);
	virtual ~Level();

	virtual void onNotify(Subject const & entity, Event event);

private:

};

#endif	/* LEVEL_HPP */
