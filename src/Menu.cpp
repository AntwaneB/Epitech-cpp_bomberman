/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Menu.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void
Menu::onNotify(Subject* entity, Event event)
{
	(void)entity;
	(void)event;
}

void
Menu::run()
{
	this->notify(new Level(10, 10, 4), LEVEL_GENERATED);
}
