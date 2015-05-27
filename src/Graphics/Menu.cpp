/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 9:20 PM
 */

#include <iostream>
#include <SFML/Audio.hpp>
#include "Graphics/Menu.hh"
#include "Core/Input.hh"

Graphics::Menu::Menu()
	: _menu(NULL)
{
	_actions[MENU_EXITED] = &Menu::exited;
}

Graphics::Menu::~Menu()
{
	_sprites.clear();
}

void
Graphics::Menu::init(::Menu* menu)
{
	_menu = menu;

	_window.create(sf::VideoMode(_menu->layout()["size"]["x"], _menu->layout()["size"]["y"]), std::string(_menu->layout()["title"]));

	// Screen background
	_backgroundTexture.loadFromFile(_menu->layout()["background"]["location"]);
	_background.setTexture(_backgroundTexture);
	_background.setScale(_menu->layout()["background"]["scale"]["x"], _menu->layout()["background"]["scale"]["y"]);

	// Text and buttons assets
	_assetsTexture.loadFromFile(_menu->layout()["assets"]["location"]);

	_cursor.setTexture(_assetsTexture);
	_cursor.setTextureRect(sf::IntRect(_menu->layout()["cursor"]["asset"]["texture"]["start_x"], _menu->layout()["cursor"]["asset"]["texture"]["start_y"], _menu->layout()["cursor"]["asset"]["texture"]["end_x"], _menu->layout()["cursor"]["asset"]["texture"]["end_y"]));
	_cursor.setScale(_menu->layout()["cursor"]["asset"]["scale"]["x"], _menu->layout()["cursor"]["asset"]["scale"]["y"]);

	_sprites.clear();
	for (auto it = _menu->layout()["content"].begin(); it != _menu->layout()["content"].end(); ++it)
	{
		Config::Param& param = it->second;

		sf::Sprite sprite;
		sprite.setTexture(_assetsTexture);
		sprite.setTextureRect(sf::IntRect(param["asset"]["texture"]["start_x"], param["asset"]["texture"]["start_y"], param["asset"]["texture"]["end_x"], param["asset"]["texture"]["end_y"]));
		sprite.setScale(param["asset"]["scale"]["x"], param["asset"]["scale"]["y"]);
		sprite.setPosition(param["asset"]["position"]["x"], param["asset"]["position"]["y"]);
		_sprites.push_back(sprite);

		if (param["selected"] == true)
		{
			_cursor.setPosition(param["cursor"]["position"]["x"], param["cursor"]["position"]["y"]);
		}
	}
}

void
Graphics::Menu::run()
{
	while (_window.isOpen())
	{
		this->draw();
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				std::map<sf::Keyboard::Key, Input::Key> keys;
				keys[sf::Keyboard::Up] = ::Input::UP;
				keys[sf::Keyboard::Down] = ::Input::DOWN;
				keys[sf::Keyboard::Right] = ::Input::RIGHT;
				keys[sf::Keyboard::Left] = ::Input::LEFT;
				keys[sf::Keyboard::Z] = ::Input::UP;
				keys[sf::Keyboard::S] = ::Input::DOWN;
				keys[sf::Keyboard::Q] = ::Input::LEFT;
				keys[sf::Keyboard::D] = ::Input::RIGHT;
				keys[sf::Keyboard::Space] = ::Input::ENTER;
				keys[sf::Keyboard::Return] = ::Input::ENTER;
				keys[sf::Keyboard::Return] = ::Input::ENTER;
				keys[sf::Keyboard::Escape] = ::Input::ESC;

				if (keys.find(event.key.code) != keys.end())
				{
					this->notify(new Input(keys.find(event.key.code)->second), KEY_PRESSED);
				}
			}
		}
	}
}

void
Graphics::Menu::update()
{
	for (auto it = _menu->layout()["content"].begin(); it != _menu->layout()["content"].end(); ++it)
	{
		Config::Param& param = it->second;

		if (param["selected"] == true)
		{
			_cursor.setPosition(param["cursor"]["position"]["x"], param["cursor"]["position"]["y"]);
		}
	}
}

void
Graphics::Menu::draw()
{
	_window.clear();

	_window.draw(_background);
	_window.draw(_cursor);

	for (auto it = _sprites.begin(); it != _sprites.end(); ++it)
	{
		_window.draw(*it);
	}

	_window.display();
}

void
Graphics::Menu::exited(Subject* entity __attribute__((unused)))
{
	_window.close();
}
