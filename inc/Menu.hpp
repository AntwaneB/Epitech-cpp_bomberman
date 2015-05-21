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

class Menu : public Subject, public EventHandler<Menu>
{
public:
	Menu();
	virtual ~Menu();

	void	run();

private:
	Config	_cfg;

};

#endif	/* MENU_HPP */
