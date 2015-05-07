/*
 ** App.cpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#include <iostream>
#include "Exception.hpp"
#include "App.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include "Graphics/Display.hh"

Config g_settings;

App::App(int ac, char** av)
	: _ac(ac), _av(av)
{
	_actions[LEVEL_GENERATED] = &App::runLevel;
	_actions[EXIT_TRIGGERED] = &App::exit;

	if (!this->validateArgs())
		throw ArgumentsException("usage:\n./bomberman");

	g_settings.importFile("config/default.xml");
}

bool
App::validateArgs() const
{
	return (true);
}

App::~App()
{
	if (this)
	{
	}
}

void
App::runLevel(Subject* entity)
{
	if (dynamic_cast<Level*>(entity))
	{
		Level* level = dynamic_cast<Level*>(entity);

		level->addObserver(this);
		level->addObserver(_display);

		_display->addObserver(level);

		level->run();
	}
	else
		throw EventException("Event thrown on not-matching entity");
}

void
App::exit(Subject* entity __attribute__((unused)))
{

}

int
App::run()
{
	_display = new Display;
	this->addObserver(_display);

	Menu* mainMenu = new Menu;
	mainMenu->addObserver(this);
	mainMenu->addObserver(_display);

	mainMenu->run();

	delete mainMenu;
	delete _display;

	return (0);
}
