/*
 * File:   Display.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 4:07 PM
 */

#ifndef DISPLAY_HH
#define	DISPLAY_HH

#include "Observer.hpp"
#include "SdlContext.hh"
#include "Game.hh"

class Display : public EventHandler<Display>, public Observer, public Subject
{
public:
	Display();
	virtual ~Display();

	virtual void onNotify(Subject* entity, Event event);

private:
	void	runMenu();
	void	runLevel();

private:
	gdl::SdlContext	_context;
};

#endif	/* DISPLAY_HH */
