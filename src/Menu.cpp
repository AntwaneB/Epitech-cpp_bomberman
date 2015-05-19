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
Menu::run()
{
	this->notify(new Level(12, 12, 9), LEVEL_GENERATED);
}
