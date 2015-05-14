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
#include "Character.hpp"
#include "App.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include "Graphics/Display.hh"
#include "Graphics/Map.hh"

Config g_settings;

App::App(int ac, char** av)
	: _ac(ac)
{
	_actions[LEVEL_GENERATED] = &App::runLevel;
	_actions[EXIT_TRIGGERED] = &App::exit;

	for (int i = 0; i < _ac; i++)
		_av.push_back(av[i]);

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
	Level* level = safe_cast<Level*>(entity);

	level->addObserver(this);

	if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
	{
		level->addObserver(_display);
		_display->addObserver(level);
	}

	level->run();
}

void
App::exit(Subject* entity __attribute__((unused)))
{
	exit(0);
}

int
App::run()
{
	if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
	{
		_display = new Graphics::Display;
		this->addObserver(_display);
	}

	Menu* mainMenu = new Menu;
	mainMenu->addObserver(this);
	if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
		mainMenu->addObserver(_display);

	mainMenu->run();

	delete mainMenu;
	if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
		delete _display;

	return (0);
}
