/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 9:20 PM
 */

#include "Graphics/Menu.hh"
#include <SFML/Audio.hpp>
#include <iostream>

Graphics::Menu::Menu()
{
	_tBackground.loadFromFile("./assets/Menu-Bomberman.png");
	_tArrow.loadFromFile("./assets/arrow.png");
	_window.create(sf::VideoMode(1920, 1080), "Boom Clap !");
    int		x;
    int		y;
	sf::SoundBuffer buff;
	buff.loadFromFile("./assets/bomberman.wav");
	sf::Sound sound;
	sound.setBuffer(buff);
	sound.play();
	
    x = 1800;
    y = 500;
    while (_window.isOpen())
    {
        sf::Event event;
        _background.setTexture(_tBackground);
        _arrow.setTexture(_tArrow);
        _arrow.setPosition(x, y);
 		_window.clear();
        _window.draw(_background);
        _window.draw(_arrow);
        _window.display();
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
            else if(event.type == sf::Event::KeyPressed)
             {
                if(event.key.code == sf::Keyboard::Down)
                { 
             		if (y >= 950)
            			y = 500;
            		else
            			y += 150;
            		update(x, y);   
                }
                else if(event.key.code == sf::Keyboard::Up)
                { 
             		if (y <= 500)
            			y = 950;
            		else
            			y -= 150;
            		update(x, y);
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                	std::cout << y << std::endl;
                	if (y == 500)
                	{
                		_tBackground.loadFromFile("./assets/Settings-Bomberman.png");
                		_background.setTexture(_tBackground);
                		_window.clear();
    					_window.draw(_background);
 						_window.display();
                	}
                	else if (y == 950)
                	{
                		_window.close();
                		exit(EXIT_SUCCESS);
                	}
                }
             }
        }
    }
}

void 		Graphics::Menu::update(int x, int y)
{
	_arrow.setPosition(x, y);
    _window.clear();
    _window.draw(_background);
 	_window.draw(_arrow);
 	_window.display();
}

Graphics::Menu::~Menu()
{
	_window.close();
}
