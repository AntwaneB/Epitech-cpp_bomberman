/*
 * File:   Menu.hpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "Core/Observer.hpp"
#include "Core/Level.hh"

class Menu : public Subject, public EventHandler<Menu>
{
public:
	Menu(const std::string &);
	virtual ~Menu();

	void		run();

	void		save(void) const;

	Config&	layout(void);

private:
	void		keyPressed(Subject*);

private:
	Config			_layout;
	std::string		_filename;

};

#endif	/* MENU_HPP */
