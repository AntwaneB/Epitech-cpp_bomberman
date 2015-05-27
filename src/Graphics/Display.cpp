/*
 * File:   Display.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 4:07 PM
 */

#include "Core/Level.hh"
#include "Graphics/Display.hh"

Graphics::Display::Display()
	: _level(NULL), _menu(NULL)
{
	_actions[LEVEL_STARTED] = &Graphics::Display::runLevel;
	_actions[LEVEL_UPDATED] = &Graphics::Display::updateLevel;
	_actions[LEVEL_PAUSE_TICK] = &Graphics::Display::updateLevelPaused;
	_actions[EXIT_TRIGGERED] = &Graphics::Display::exitGame;
	_actions[MENU_STARTED] = &Graphics::Display::runMenu;
}

Graphics::Display::~Display()
{
}

void
Graphics::Display::exitGame(Subject* entity __attribute__((unused)))
{
	this->notify(this, EXIT_TRIGGERED);
}

void
Graphics::Display::runMenu(Subject* entity)
{
	::Menu*	menu = safe_cast<::Menu*>(entity);

	if (_menu != NULL)
	{
		delete _menu;
		_menu = NULL;
	}
	_menu = new Graphics::Menu(menu);
}

void
Graphics::Display::updateMenu(Subject* entity)
{
	::Menu*	menu = safe_cast<::Menu*>(entity);

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
	_level->addObserver(this);
	_level->addObserver(level);
}

void
Graphics::Display::updateLevel(Subject* entity __attribute__((unused)))
{
	_level->update();
	_level->draw();
}

void
Graphics::Display::updateLevelPaused(Subject* entity __attribute__((unused)))
{
	_level->updateInput();
}
