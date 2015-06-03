/*
 * File:   Display.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 4:07 PM
 */

#include <unistd.h>
#include "global.hh"
#include "Core/Level.hh"
#include "Graphics/Display.hh"

Graphics::Display::Display()
	: _level(NULL), _menu(NULL), _audioManager(10)
{
	_actions[LEVEL_STARTED] = &Graphics::Display::runLevel;
	_actions[LEVEL_ENDED] = &Graphics::Display::endLevel;
	_actions[LEVEL_UPDATED] = &Graphics::Display::updateLevel;
	_actions[LEVEL_PAUSE_TICK] = &Graphics::Display::updateLevelPaused;
	_actions[EXIT_TRIGGERED] = &Graphics::Display::exitGame;
	_actions[MENU_STARTED] = &Graphics::Display::runMenu;
	_actions[MENU_UPDATED] = &Graphics::Display::updateMenu;
	_actions[MENU_EXITED] = &Graphics::Display::exitMenu;

	_actions[LEVEL_BOMB_EXPLODED] = &Graphics::Display::bombExploded;
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
	if (_level != NULL)
	{
		delete _level;
		_level = NULL;
	}

	::Menu*	menu = safe_cast<::Menu*>(entity);

	if (_menu == NULL)
	{
		_menu = new Graphics::Menu();
		_menu->addObserver(this);
	}

	_audioManager.playMusic(g_settings["sounds"]["menu_started"], true);

	_menu->addObserver(menu);
	_menu->init(menu);
	_menu->run();
}

void
Graphics::Display::exitMenu(Subject* entity)
{
	::Menu*	menu = safe_cast<::Menu*>(entity);

	if (_menu != NULL)
	{
		this->notify(menu, MENU_EXITED, _menu);

		this->removeObserver(menu);
		this->removeObserver(_menu);
		menu->removeObserver(_menu);

		_menu = NULL;
	}
}

void
Graphics::Display::updateMenu(Subject* entity __attribute__((unused)))
{
	if (_menu)
	{
		_menu->update();
		_menu->draw();
	}
}

void
Graphics::Display::runLevel(Subject* entity)
{
	if (_level != NULL)
	{
		delete _level;
		_level = NULL;
	}

	_audioManager.stopMusic(g_settings["sounds"]["menu_started"]);
	_audioManager.playMusic(g_settings["sounds"]["level_started"], true);

	::Level*	level = safe_cast<::Level*>(entity);

	_level = new Graphics::Level(level);
	_level->addObserver(this);
	_level->addObserver(level);
}

void
Graphics::Display::endLevel(Subject* entity __attribute__((unused)))
{
	if (_level != NULL)
	{
		delete _level;
		_level = NULL;
	}

	_audioManager.stopMusic(g_settings["sounds"]["level_started"]);
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

void
Graphics::Display::bombExploded(Subject* entity __attribute__((unused)))
{
	_audioManager.playSound(g_settings["sounds"]["bomb_exploded"]);
}
