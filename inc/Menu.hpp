/*
 * File:   Menu.hpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "Observer.hpp"
#include "Level.hpp"

class Menu : public Subject, public Observer
{
public:
	Menu();
	virtual ~Menu();

	void	run();

	void	onNotify(Subject* entity, Event event);

private:

};

#endif	/* MENU_HPP */
