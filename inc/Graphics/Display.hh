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

class Display : public EventHandler<Display>, public Subject
{
public:
	Display();
	virtual ~Display();

private:
	void	runMenu();
	void	runLevel();
};

#endif	/* DISPLAY_HH */
