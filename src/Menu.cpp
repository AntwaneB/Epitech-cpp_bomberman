/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Core/Menu.hh"

Menu::Menu(const std::string & filename) : _filename(filename)
{
	_cfg.importFile(_filename);
	_actions[Input::UP] = &Menu::moveUp;
	_actions[Input::DOWN] = &Menu::moveDown;
	_actions[Input::LEFT] = &Menu::moveLeft;
	_actions[Input::RIGHT] = &Menu::moveRight;
	_actions[Input::ENTER] = &Menu::select;
	_actions[KEY_ENTER] = &Menu::select;

	if (_cfg["content"].isEmpty())
		throw ConfigException("File " + filename + " is not valid");
}

Menu::~Menu()
{
}

void
Menu::save(void) const
{
	_cfg.exportFile(_filename);
}

void
Menu::run()
{
}

void
Menu::moveUp(void)
{
	Config	arrow = getArrow();
	Config	current = getCurrent();
}

void
Menu::moveDown(void)
{
	Config	arrow = getArrow();
	Config	current = getCurrent();
}

void
Menu::moveLeft(void)
{
	Config	current = getCurrent();
}

void
Menu::moveRight(void)
{
	Config	current = getCurrent();
}

void
Menu::select(void)
{
	Config	current = getCurrent();
}

Config&
Menu::getArrow(void) const
{
}

Config&
Menu::getCurrent(void) const
{
	Config	items;

	items = _cfg["content"];
	for (auto it = items.begin(); it != items.end(); ++it)
		if ((*it)["selectable"] == "true" && (*it)["selected"] == "true")
			return (*it);
	return (items.end());
}

Config&
Menu::getConfig(void) const
{
	return _cfg;
}
