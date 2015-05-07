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
/*	Menu* mainMenu = new Menu;
	mainMenu->addObserver(this);

	mainMenu->run();

	delete mainMenu;*/

	// operations.insert(std::map<std::string, void (Parser::*)
	// (std::vector<std::string> const &)>::value_type("push", &Parser::push));

	std::map<Position, std::list<Character *> > mymap;
	try
	{
		std::list<Character *> my_list;
		Position p(1, 1, 15);
		Character *c = new Character();
		my_list.push_back(c);
		mymap.insert (std::map<Position, std::list<Character *> >::value_type(p, my_list));
		Map m("maps/default.xml", mymap);
/*		Map m(atoi(_av[1]), atoi(_av[2]), mymap);*/
	}
	catch (Exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
