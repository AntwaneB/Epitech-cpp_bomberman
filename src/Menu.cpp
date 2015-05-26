/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Graphics/Menu.hh"
#include "Core/Menu.hh"

Menu::Menu(const std::string & filename) : _filename(filename)
{
	_cfg.importFile(_filename);
	_actions[KEY_PRESSED] = &Menu::keyPressed;

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
	this->notify(this, MENU_STARTED);
}

void
Menu::keyPressed(Subject* entity)
{
	Input*	input = safe_cast<Input*>(entity);
	Config	current;

	current = getCurrent();
	switch (input->genericKey())
	{
		case (Input::UP):
		{
			break;
		}
		case (Input::DOWN):
		{
			break;
		}
		case (Input::LEFT):
		{
			break;
		}
		case (Input::RIGHT):
		{
			break;
		}
		case (Input::SPACE):
		{
			break;
		}
		default:
		{
			break;
		}
	}
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
Menu::getPrev(Config & current) const
{
	Config	items;
	int	id;

	id = current["order"] - 1;
	if (id == 0)
		return getLast();

	items = _cfg["content"];

	for (auto it = items.begin(); it != items.end(); ++it)
		if ((*it)["order"] == id )
			return (*it);
	return (items.end());
}

Config&
Menu::getNext(Config & current) const
{
	return (_cfg);
}

Config&
Menu::getLast(void) const
{
	Config	items;
	Config*	tmp;
	int		max;

	items = _cfg["content"];
	tmp = &(items.end());
	max = 0;

	for (auto it = items.begin(); it != items.end(); ++it)
		if ((*it)["order"] >= max)
		{
			max = ((*it)->second)["order"];
			tmp = &(*it);
		}
	return (*tmp);
}

Config&
Menu::getConfig(void) const
{
	return _cfg;
}
