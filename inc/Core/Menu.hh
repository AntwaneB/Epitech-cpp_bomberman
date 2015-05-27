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
	void		runLine(Input::Key);
	void		quit(Input::Key);

	void		actionNewMenu(std::string const &);
	void		actionRunLevel(std::string const &);
	void		actionLoadLevel(std::string const &);
	void		actionExit(std::string const &);

private:
	Config			_layout;
	std::string		_filename;

private:
	std::map<std::string, void (Menu::*)(std::string const &)>	_menuActions;
};

#endif	/* MENU_HPP */
