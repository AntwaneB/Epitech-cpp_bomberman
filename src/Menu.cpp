/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Graphics/Menu.hh"
#include "Core/Menu.hh"
#include "Core/Input.hh"

Menu::Menu(const std::string & filename)
	: _filename(filename)
{
	_actions[KEY_PRESSED] = &Menu::keyPressed;

	_menuActions["NEW_MENU"] = &Menu::actionNewMenu;
	_menuActions["RUN_LEVEL"] = &Menu::actionRunLevel;
	_menuActions["LOAD_LEVEL"] = &Menu::actionLoadLevel;
	_menuActions["EXIT"] = &Menu::actionExit;

	_layout.importFile(_filename);
	if (_layout["content"].isEmpty())
		throw ConfigException("File " + filename + " is not valid");
}

Menu::~Menu()
{
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

	std::map<Input::Key, void (Menu::*)(Input::Key)> actions;
	actions[Input::UP] = &Menu::changeLine;
	actions[Input::DOWN] = &Menu::changeLine;
	actions[Input::LEFT] = &Menu::changeValue;
	actions[Input::RIGHT] = &Menu::changeValue;
	actions[Input::SPACE] = &Menu::runLine;
	actions[Input::ENTER] = &Menu::runLine;
	actions[Input::ESC] = &Menu::quit;

	if (actions.find(input->genericKey()) != actions.end())
		(this->*(actions[input->genericKey()]))(input->genericKey());

	this->notify(this, MENU_UPDATED);
}

Config&
Menu::layout(void)
{
	return _layout;
}

void
Menu::changeLine(Input::Key key)
{
	size_t count = 0;

	Config::Param* active;
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["selected"] == true)
			active = &(it->second);
		if (it->second["selectable"] == true)
			count++;
	}

	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (key == Input::UP)
		{
			if (&(it->second) != active
				&& it->second["selectable"] == true
				&& (it->second["order"] == static_cast<int>((*active)["order"]) - 1 || ((*active)["order"] == 1 && static_cast<size_t>(it->second["order"]) == count)))
			{
				it->second["selected"] = true;
			}
		}
		else if (key == Input::DOWN)
		{
			if (&(it->second) != active
					&& it->second["selectable"] == true
					&& (it->second["order"] == static_cast<int>((*active)["order"]) + 1 || (static_cast<size_t>((*active)["order"]) == count
																												  && static_cast<size_t>(it->second["order"]) == 1)))
			{
				it->second["selected"] = true;
			}
		}
	}
	(*active)["selected"] = false;
}

void
Menu::changeValue(Input::Key key)
{
	Config::Param* active;
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["selected"] == true)
			active = &(it->second);
	}

	int newValue = (*active)["value"]["value"];
	newValue = key == Input::LEFT ? newValue - 1 : newValue + 1;
	newValue = (*active)["value"]["min"] > newValue ? (*active)["value"]["max"] : newValue;
	newValue = (*active)["value"]["max"] < newValue ? (*active)["value"]["min"] : newValue;

	(*active)["value"]["value"] = newValue;
}

void
Menu::runLine(Input::Key key __attribute__((unused)))
{
	Config::Param* active;
	for (auto it = _layout["content"].begin(); it != _layout["content"].end(); ++it)
	{
		if (it->second["selected"] == true)
			active = &(it->second);
	}

	if (_menuActions.find((*active)["action"]["name"]) != _menuActions.end())
		(this->*(_menuActions[(*active)["action"]["name"]]))((*active)["action"]["param"]);
}

void
Menu::quit(Input::Key key __attribute__((unused)))
{
	this->notify(this, EXIT_TRIGGERED);
}

void
Menu::actionNewMenu(const std::string& param)
{
//	this->notify(this, MENU_EXITED);
	this->notify(new Menu(param), MENU_STARTED);
}

void
Menu::actionLoadLevel(const std::string& param)
{
	(void)param;
}

void
Menu::actionRunLevel(const std::string& param __attribute__((unused)))
{
	size_t width = _layout["content"]["width"]["value"]["value"];
	size_t height = _layout["content"]["height"]["value"]["value"];
	size_t iaCount = _layout["content"]["ias"]["value"]["value"];
	size_t playerCount = _layout["content"]["players"]["value"]["value"];

	std::cout << "Generating new level with settings :" << std::endl;
	std::cout << "- Width : " << width << std::endl;
	std::cout << "- Height : " <<  height << std::endl;
	std::cout << "- IA Count : " <<  iaCount << std::endl;
	std::cout << "- Player Count : " <<  playerCount << std::endl;

	this->notify(this, MENU_EXITED);
	this->notify(new Level(width, height, iaCount + playerCount, playerCount), LEVEL_GENERATED);
}

void
Menu::actionExit(const std::string& param __attribute__((unused)))
{
	this->quit(Input::ESC);
}
