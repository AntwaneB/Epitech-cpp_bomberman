/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Menu.hpp"

Menu::Menu(const std::string & filename) : _filename(filename)
{
	_cfg.importFile(_filename);
}

Menu::~Menu()
{
}

void
Menu::save(void) const
{
	_cfg.exportFile(_filename);
}

void
Menu::run()
{
	this->notify(new Level(12, 12, 9, 2), LEVEL_GENERATED);
}
