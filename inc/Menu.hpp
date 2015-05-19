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
	Menu(const std::string &);
	virtual ~Menu();

	void	run();

private:

};

#endif	/* MENU_HPP */
