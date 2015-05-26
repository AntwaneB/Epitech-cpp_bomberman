/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 5, 2015, 8:53 PM
 */

#include <iostream>
#include "Core/Menu.hh"

Menu::Menu(const std::string & filename) : _filename(filename)
{
	_cfg.importFile(_filename);
	_actions[Input::UP] = &Menu::moveUp;
	_actions[Input::DOWN] = &Menu::moveDown;
	_actions[Input::LEFT] = &Menu::moveLeft;
	_actions[Input::RIGHT] = &Menu::moveRight;
	_actions[Input::ENTER] = &Menu::select;
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


std::map<std::string, Graphics::Menu::Item*>&
Menu::getItems(void) const
{
	return _items;
}
