/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Core/Menu.hh"
#include "Core/Input.hh"

Menu::Menu(const std::string & filename) : _filename(filename)
{
	_cfg.importFile(_filename);

	if (_cfg["content"].isEmpty())
		throw ConfigException("File " + filename + " is not valid");
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
	this->notify(new Level(12, 12, 9, 1), LEVEL_GENERATED);
}

void
Menu::moveUp(void)
{
}

void
Menu::moveDown(void)
{
}

void
Menu::moveLeft(void)
{
}

void
Menu::moveRight(void)
{
}

void
Menu::select(void)
{
}
