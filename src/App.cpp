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
#include "Map.hpp"
#include "Exception.hpp"
#include "Character.hpp"
#include "App.hpp"
#include "Level.hpp"
#include "App.hpp"
#include "Map.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av)
{
	_actions[LEVEL_GENERATED] = &App::runLevel;
	_actions[EXIT_TRIGGERED] = &App::exit;
/*	Display a;*/
/*	while (42)
	{
	}*/
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
/*	Menu* mainMenu = new Menu;
	_display = new Display;
	this->addObserver(_display);

	Menu* mainMenu = new Menu;
	mainMenu->addObserver(_display);

	mainMenu->run();

	delete mainMenu;
	delete mainMenu;
	delete _display; */

	// operations.insert(std::map<std::string, void (Parser::*)
	// (std::vector<std::string> const &)>::value_type("push", &Parser::push));

	std::map<Position, std::list<Character *> > mymap;
	try
	{
		std::list<Character *> my_list;
		Position p(1, 1, 15);
		Character *c = new Character(1, 5, 6, 8);
		my_list.push_back(c);
		mymap.insert (std::map<Position, std::list<Character *> >::value_type(p, my_list));
		Map m("maps/default.xml", mymap);
/*		Map m(atoi(_av[1]), atoi(_av[2]));*/
	}
	catch (Exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
