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
#include "Graphics/Display.hh"
#include "Map.hpp"
#include "Exception.hpp"
#include "App.hpp"
#include "Menu.hpp"
#include "Level.hpp"
#include "App.hpp"
#include "Map.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av)
{
	if (!this->validateArgs())
		throw ArgumentsException("usage:\n" \
										 "./bomberman");

	_actions[LEVEL_GENERATED] = &App::runLevel;
	_actions[EXIT_TRIGGERED] = &App::exit;
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
App::onNotify(Subject * entity, Event event)
{
	auto it = _actions.find(event);

	if (it != _actions.end())
	{
		(this->*(it->second))(entity);
	}
}

void
App::runLevel(Subject* entity)
{
	Level* level = dynamic_cast<Level*>(entity);

	std::cout << "App::runLevel()" << std::endl;

	delete level;
}

void
App::exit(Subject* entity __attribute__((unused)))
{

}

int
App::run()
{
	Menu* mainMenu = new Menu;
	mainMenu->addObserver(this);

	mainMenu->run();

	delete mainMenu;

	/*
	std::map<Position *, int> mymap;
	try
	{
		Position *p = new Position(1, 1, 15);
		Position *p2 = new Position(9, 15, 15);
		mymap.insert (std::pair<Position *,int>(p,100));
		mymap.insert (std::pair<Position *, int>(p2, 100));
		Map m(atoi(_av[1]), atoi(_av[2]), mymap);
	}
	catch (Exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	*/

	return (0);
}
