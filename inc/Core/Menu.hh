/*
 * File:   Menu.hpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "Observer.hpp"
#include "Level.hh"

class Menu : public Subject, public EventHandler<Menu>
{
public:
	Menu(const std::string &);
	virtual ~Menu();

	void	run();

	void	save(void) const;

private:
	Config		_cfg;
	std::string	_filename;

};

#endif	/* MENU_HPP */
