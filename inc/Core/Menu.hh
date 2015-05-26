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

	Config&		getConfig(void);

private:
	void		keyPressed(Subject*);
	// Config&		getArrow(void);
	// Config&		getCurrent(void);
	// Config&		getPrev(Config&);
	// Config&		getNext(Config&);
	// Config&		getLast(void);

private:
	Config			_cfg;
	std::string		_filename;

};

#endif	/* MENU_HPP */
