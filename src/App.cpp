/*
 ** App.cpp
 **
 ** Made by Antoine Buchser
 ** Login   <buchse_a@epitech.eu>
 **
 ** Started on February 6, 2015, 10:53 AM Antoine Buchser
 ** Updated on February 6, 2015, 10:53 AM Antoine Buchser
 */

#include "Map.hpp"
#include "Exception.hpp"
#include "App.hpp"

App::App(int ac, char** av)
	: _ac(ac), _av(av)
{
	if (!this->validateArgs())
		throw ArgumentsException("usage:\n" \
										 "./bomberman");
}

App::~App()
{
	if (this)
	{
	}
}

bool	App::validateArgs() const
{
	return (true);
}

int	App::run()
{
	Map map(42, 42);

	return (0);
}
