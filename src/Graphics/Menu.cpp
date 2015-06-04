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
#include "Core/Menu.hh"

Graphics::Menu::Menu()
	: _menu(NULL), _run(false)
{
	_actions[MENU_EXITED] = &Menu::exited;
}

Graphics::Menu::~Menu()
{
	_sprites.clear();
	_window.close();
}

void
Graphics::Menu::init(::Menu* menu)
{
	if (_menu)
	{
		this->removeObserver(_menu);
		_menu->removeObserver(this);
	}

	_menu = menu;

	if (!_window.isOpen())
		_window.create(sf::VideoMode(_menu->layout()["size"]["x"], _menu->layout()["size"]["y"]), std::string(_menu->layout()["title"]));
	else
		_window.clear();
	_window.setPosition(sf::Vector2i(1920/4, 1080/4));

	// Screen background
	_backgroundTexture.loadFromFile(_menu->layout()["background"]["location"]);
	_background.setTexture(_backgroundTexture);
	_background.setScale(_menu->layout()["background"]["scale"]["x"], _menu->layout()["background"]["scale"]["y"]);

	// Text and buttons assets
	_assetsTexture.loadFromFile(_menu->layout()["assets"]["location"]);

	if (_menu->hasSelectable())
	{
		_cursor.setTexture(_assetsTexture);
		_cursor.setTextureRect(sf::IntRect(_menu->layout()["cursor"]["asset"]["texture"]["start_x"], _menu->layout()["cursor"]["asset"]["texture"]["start_y"], _menu->layout()["cursor"]["asset"]["texture"]["width"], _menu->layout()["cursor"]["asset"]["texture"]["height"]));
		_cursor.setScale(_menu->layout()["cursor"]["asset"]["scale"]["x"], _menu->layout()["cursor"]["asset"]["scale"]["y"]);
	}

	_sprites.clear();

	_font.loadFromFile("./assets/ocraextended.ttf");

	for (auto it = _menu->layout()["content"].begin(); it != _menu->layout()["content"].end(); ++it)
	{
		Config::Param& param = it->second;

		if (param["is_collection"] == false)
		{
			if (param["type"] != "value_only")
			{
				sf::Sprite sprite;
				sprite.setTexture(_assetsTexture);
				sprite.setTextureRect(sf::IntRect(param["asset"]["texture"]["start_x"], param["asset"]["texture"]["start_y"], param["asset"]["texture"]["width"], param["asset"]["texture"]["height"]));
				sprite.setScale(param["asset"]["scale"]["x"], param["asset"]["scale"]["y"]);
				sprite.setPosition(param["asset"]["position"]["x"], param["asset"]["position"]["y"]);
				_sprites.push_back(sprite);
			}

			if (_menu->hasSelectable() && param["selected"] == true)
				_cursor.setPosition(param["cursor"]["position"]["x"], param["cursor"]["position"]["y"]);

			if (param["has_value"] == true)
			{
				sf::Text text;
				text.setFont(_font);
				text.setString(static_cast<std::string>(param["value"]["value"]));
				text.setCharacterSize(param["value"]["size"]);
				text.setColor(param["type"] != "value_only" ? sf::Color(254, 221, 0) : sf::Color::White);
				text.setPosition(param["value"]["x"], param["value"]["y"]);
				_texts[&param] = text;
			}
		}
		else
		{
			for (auto value = param["collection"]["values"].begin(); value != param["collection"]["values"].end(); ++value)
			{
				sf::Text text;
				text.setFont(_font);
				text.setString(static_cast<std::string>(value->second));
				text.setCharacterSize(param["collection"]["font_size"]);
				text.setColor(sf::Color(254, 221, 0));
				text.setPosition(param["position"]["min_x"], static_cast<int>(param["position"]["min_y"]) + std::stoi(value->first) * (5 + static_cast<int>(param["collection"]["font_size"])));
				_collections[&param].push_back(text);
			}
		}
	}

	_run = true;
}

void
Graphics::Menu::run()
{
	while (_window.isOpen() && _run)
	{
		this->draw();
		sf::Event event;
		while (_run && _window.pollEvent(event))
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
					this->notify(new Input(keys.find(event.key.code)->second), KEY_PRESSED, _menu);
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

		if (param["is_collection"] == false)
		{
			if (_menu->hasSelectable() && param["selected"] == true)
				_cursor.setPosition(param["cursor"]["position"]["x"], param["cursor"]["position"]["y"]);
			if (param["has_value"] == true)
				_texts[&param].setString(static_cast<std::string>(param["value"]["value"]));
		}
	}
}

void
Graphics::Menu::draw()
{
	_window.clear();

	_window.draw(_background);
	if (_menu->hasSelectable())
		_window.draw(_cursor);

	for (auto it = _sprites.begin(); it != _sprites.end(); ++it)
	{
		_window.draw(*it);
	}
	for (auto it = _texts.begin(); it != _texts.end(); ++it)
	{
		_window.draw(it->second);
	}
	for (auto it = _collections.begin(); it != _collections.end(); ++it)
	{
		for (auto yt = it->second.begin(); yt != it->second.end(); ++yt)
			_window.draw(*yt);
	}

	_window.display();
}

void
Graphics::Menu::exited(Subject* entity __attribute__((unused)))
{
	_run = false;
	_window.close();
}
