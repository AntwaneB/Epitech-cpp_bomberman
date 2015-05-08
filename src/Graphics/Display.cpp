/*
 * File:   Display.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 4:07 PM
 */

#include "Level.hpp"
#include "Graphics/Display.hh"

Graphics::Display::Display()
	: _level(NULL), _menu(NULL)
{
	_actions[LEVEL_STARTED] = &Graphics::Display::runLevel;
	_actions[LEVEL_UPDATED] = &Graphics::Display::updateLevel;
}

Graphics::Display::~Display()
{
}

void
Graphics::Display::runMenu(Subject* entity)
{
	Menu*	menu = safe_cast<Menu*>(entity);

	(void)menu;
}

void
Graphics::Display::updateMenu(Subject* entity)
{
	Menu*	menu = safe_cast<Menu*>(entity);

	(void)menu;
}

void
Graphics::Display::runLevel(Subject* entity)
{
	::Level*	level = safe_cast<::Level*>(entity);

	if (_level != NULL)
	{
		delete _level;
		_level = NULL;
	}
	_level = new Graphics::Level(level);
}

void
Graphics::Display::updateLevel(Subject* entity)
{
	::Level*	level = safe_cast<::Level*>(entity);
	(void)level;

	_level->update();
}
