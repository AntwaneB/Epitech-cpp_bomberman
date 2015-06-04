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
#include "Core/Config.hh"

class Menu : public Subject, public EventHandler<Menu>
{
public:
	Menu(const std::string &, const Level * level = NULL);
	virtual ~Menu();

	void		run();
	Config&	layout(void);
	bool		hasSelectable() const;

private:
	void		keyPressed(Subject*);

private:
	void		init();
	void		buildFilesCollection(Config::Param&);

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
	const Level*	_level;
	bool				_hasSelectable;
};

#endif	/* MENU_HPP */
