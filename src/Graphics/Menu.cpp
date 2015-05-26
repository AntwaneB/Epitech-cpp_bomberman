/*
 * File:   Menu.cpp
 * Author: buchse_a
 *
 * Created on May 6, 2015, 9:20 PM
 */

#include "Graphics/Menu.hh"
#include <SFML/Audio.hpp>
#include <iostream>

void
Graphics::Menu::NewGame()
{
    std::cout << "COUCOU" << std::endl;
    _window.clear();
    _tSubBackground.loadFromFile("./assets/bomber.png");
    _subBackground.setTexture(_tSubBackground);
    _subBackground.setScale(0.5f, 0.5f);
    _window.draw(_subBackground);
    std::cout << "COUCOU" << std::endl;
    sf::Event event;

    while (_window.isOpen())
    {
     while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                exit(EXIT_SUCCESS);
                _window.close();
            }
        }
    }
}

Graphics::Menu::Menu()
{
	//son
	sf::SoundBuffer buff;
	buff.loadFromFile("./assets/bomberman.wav");
	sf::Sound sound;
	sound.setBuffer(buff);
	sound.play();

	_tBackground.loadFromFile("./assets/mainmenu.png");
	_tassets.loadFromFile("./assets/asset.png");
	_window.create(sf::VideoMode(960, 540), "Boom Clap !");
	int x = 565;
    int y = 338;

    //init images
    _background.setTexture(_tBackground);
    _background.setScale(0.5f, 0.5f);

    _newgame.setTexture(_tassets);
    _newgame.setTextureRect(sf::IntRect(0, 8, 566, 100));
    _newgame.setScale(0.5f, 0.5f);
    _newgame.setPosition(600, 330);

    _loadgame.setTexture(_tassets);
    _loadgame.setTextureRect(sf::IntRect(0, 128, 646, 100));
    _loadgame.setScale(0.5f, 0.5f);
    _loadgame.setPosition(600, 380);

    _setting.setTexture(_tassets);
    _setting.setTextureRect(sf::IntRect(0, 242, 574, 130));
    _setting.setScale(0.5f, 0.5f);
    _setting.setPosition(600, 430);

    _exit.setTexture(_tassets);
    _exit.setTextureRect(sf::IntRect(0, 372, 287, 100));
    _exit.setScale(0.5f, 0.5f);
    _exit.setPosition(600, 480);

	_quote.setTexture(_tassets);
    _quote.setTextureRect(sf::IntRect(1100, 600, 1880, 100));
    _quote.setScale(0.5f, 0.5f);
    _quote.setPosition(30, 450);

    _rya.setTexture(_tassets);
    _rya.setTextureRect(sf::IntRect(1100, 503, 780, 100));
    _rya.setScale(0.5f, 0.5f);
    _rya.setPosition(x, y);

	 while (_window.isOpen())
    {

        //affichage
 		_window.clear();
        _window.draw(_background);
        _window.draw(_newgame);
		_window.draw(_loadgame);
		_window.draw(_setting);
		_window.draw(_quote);
        _window.draw(_exit);
        _window.draw(_rya);
        _window.display();
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
            	exit(EXIT_SUCCESS);
                _window.close();
            }
            else if(event.type == sf::Event::KeyPressed)
             {
                if(event.key.code == sf::Keyboard::Down)
                { 
                //	this->notify(this, KEY_PRESSED_P1_DOWN);
             		if (y >= 488)
            			y = 338;
            		else
            			y += 50;
            		update(x, y);   
                }
                else if(event.key.code == sf::Keyboard::Up)
                { 
             		if (y <= 338)
            			y = 488;
            		else
            			y -= 50;
            		update(x, y);
                }
                else if (event.key.code == sf::Keyboard::Return)
                {
                	if (y == 338)
                	{
                	   NewGame();
                	}
                	else if (y == 488)
                	{
                		_window.close();
                		exit(EXIT_SUCCESS);
                	}
                }
             }
        }
    }
}

void
Graphics::Menu::displayMenu(::Menu *)
{
    //this->notify(new ::Input(KEY_UP), KEY_PRESSED);
}

void 		Graphics::Menu::update(int x, int y)
{
	_window.clear();
    _window.draw(_background);
    _window.draw(_newgame);
	_window.draw(_loadgame);
	_window.draw(_setting);
	_window.draw(_quote);
    _window.draw(_exit);
    _rya.setPosition(x, y);
    _window.draw(_rya);
    _window.display();
}

Graphics::Menu::~Menu()
{
	_window.close();
}
