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
	_actions[KEY_UP] = &Menu::moveUp;
	_actions[KEY_DOWN] = &Menu::moveDown;
	_actions[KEY_LEFT] = &Menu::moveLeft;
	_actions[KEY_RIGHT] = &Menu::moveRight;
	_actions[KEY_ENTER] = &Menu::select;
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
	this->notify(this, MENU_STARTED);
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
