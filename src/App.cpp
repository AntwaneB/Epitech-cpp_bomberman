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
#include "Core/Character.hh"
#include "Core/App.hh"
#include "Core/Level.hh"
#include "Core/Config.hh"
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
		this->addObserver(level);
	}

	level->run();
}

void
App::exit(Subject* entity __attribute__((unused)))
{
	throw ExitException("Exiting normally");
}

int
App::run()
{
	try
	{
		if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
		{
			_display = new Graphics::Display;
			this->addObserver(_display);
			_display->addObserver(this);
		}

		Menu* mainMenu = new Menu("menus/main.xml");
		mainMenu->addObserver(this);
		if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
			mainMenu->addObserver(_display);

		try
		{
			mainMenu->run();
		}
		catch (ExitException const & e)
		{
			delete mainMenu;
			throw e;
		}

		delete mainMenu;
	}
	catch (ExitException const & e)
	{
		if (std::find(_av.begin(), _av.end(), "--gui") != _av.end())
			delete _display;
		return (EXIT_SUCCESS);
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (0);
}
