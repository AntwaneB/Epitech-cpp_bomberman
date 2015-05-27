/*
 * File:   Menu.hpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "Core/Observer.hpp"
#include "Core/Input.hh"
#include "Core/Level.hh"

class Menu : public Subject, public EventHandler<Menu>
{
public:
	Menu(const std::string &);
	virtual ~Menu();

	void		run();
	Config&	layout(void);

private:
	void		keyPressed(Subject*);

private:
	void		changeLine(Input::Key);
	void		changeValue(Input::Key);
	void		runLine();
	void		quit();

private:
	Config			_layout;
	std::string		_filename;

};

#endif	/* MENU_HPP */
