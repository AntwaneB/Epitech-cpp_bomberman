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

Graphics::Menu::Menu(::Menu* menu)
{
	Config	cfg;

	cfg = menu->getConfig();

	//sound
	sf::SoundBuffer	soundBuff;
	soundBuff.loadFromFile(cfg["sound"]);
	sf::Sound	sound;
	sound.setBuffer(soundBuff);
	sound.play();

	//window
	_window.create(sf::VideoMode(cfg["size"]["x"], cfg["size"]["y"]), std::string(cfg["title"]));

	//background
	_tBackground.loadFromFile(cfg["background"]["location"]);
	_background.setTexture(_tBackground);
	_background.setScale(cfg["background"]["scale"]["x"],cfg["background"]["scale"]["y"]);

	//assets
	_tassets.loadFromFile(cfg["assets"]["location"]);

	//content (OLD METHOD)
	//newgame
	_newgame.setTexture(_tassets);
	_newgame.setTextureRect(sf::IntRect(cfg["content"]["start"]["asset"]["texture"]["pos1"], cfg["content"]["start"]["asset"]["texture"]["pos2"], cfg["content"]["start"]["asset"]["texture"]["pos3"], cfg["content"]["start"]["asset"]["texture"]["pos4"]));
	_newgame.setScale(cfg["content"]["start"]["asset"]["scale"]["x"], cfg["content"]["start"]["asset"]["scale"]["y"]);
	_newgame.setPosition(cfg["content"]["start"]["asset"]["position"]["x"], cfg["content"]["start"]["asset"]["position"]["y"]);
	//loadgame
	_loadgame.setTexture(_tassets);
	_loadgame.setTextureRect(sf::IntRect(cfg["content"]["load"]["asset"]["texture"]["pos1"], cfg["content"]["load"]["asset"]["texture"]["pos2"], cfg["content"]["load"]["asset"]["texture"]["pos3"], cfg["content"]["load"]["asset"]["texture"]["pos4"]));
	_loadgame.setScale(cfg["content"]["load"]["asset"]["scale"]["x"], cfg["content"]["load"]["asset"]["scale"]["y"]);
	_loadgame.setPosition(cfg["content"]["load"]["asset"]["position"]["x"], cfg["content"]["load"]["asset"]["position"]["y"]);
	//settings
	_setting.setTexture(_tassets);
	_setting.setTextureRect(sf::IntRect(cfg["content"]["setting"]["asset"]["texture"]["pos1"], cfg["content"]["setting"]["asset"]["texture"]["pos2"], cfg["content"]["setting"]["asset"]["texture"]["pos3"], cfg["content"]["setting"]["asset"]["texture"]["pos4"]));
	_setting.setScale(cfg["content"]["setting"]["asset"]["scale"]["x"], cfg["content"]["setting"]["asset"]["scale"]["y"]);
	_setting.setPosition(cfg["content"]["setting"]["asset"]["position"]["x"], cfg["content"]["setting"]["asset"]["position"]["y"]);
	//exit
	_exit.setTexture(_tassets);
	_exit.setTextureRect(sf::IntRect(cfg["content"]["exit"]["asset"]["texture"]["pos1"], cfg["content"]["exit"]["asset"]["texture"]["pos2"], cfg["content"]["exit"]["asset"]["texture"]["pos3"], cfg["content"]["exit"]["asset"]["texture"]["pos4"]));
	_exit.setScale(cfg["content"]["exit"]["asset"]["scale"]["x"], cfg["content"]["exit"]["asset"]["scale"]["y"]);
	_exit.setPosition(cfg["content"]["exit"]["asset"]["position"]["x"], cfg["content"]["exit"]["asset"]["position"]["y"]);
	//quote
	_quote.setTexture(_tassets);
	_quote.setTextureRect(sf::IntRect(cfg["content"]["quote"]["asset"]["texture"]["pos1"], cfg["content"]["quote"]["asset"]["texture"]["pos2"], cfg["content"]["quote"]["asset"]["texture"]["pos3"], cfg["content"]["quote"]["asset"]["texture"]["pos4"]));
	_quote.setScale(cfg["content"]["quote"]["asset"]["scale"]["x"], cfg["content"]["quote"]["asset"]["scale"]["y"]);
	_quote.setPosition(cfg["content"]["quote"]["asset"]["position"]["x"], cfg["content"]["quote"]["asset"]["position"]["y"]);
	//arrow
	_rya.setTexture(_tassets);
	_rya.setTextureRect(sf::IntRect(cfg["content"]["arrow"]["asset"]["texture"]["pos1"], cfg["content"]["arrow"]["asset"]["texture"]["pos2"], cfg["content"]["arrow"]["asset"]["texture"]["pos3"], cfg["content"]["arrow"]["asset"]["texture"]["pos4"]));
	_rya.setScale(cfg["content"]["arrow"]["asset"]["scale"]["x"], cfg["content"]["arrow"]["asset"]["scale"]["y"]);
	_rya.setPosition(cfg["content"]["arrow"]["asset"]["position"]["x"], cfg["content"]["arrow"]["asset"]["position"]["y"]);

	//content (TODO)
	/*Config	items;
	items = cfg["content"];
	for (auto it = items.begin(); it != items.end(); ++it)
	{

	}*/
}
/*
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
*/
/*void
Graphics::Menu::initialize(::Menu* menu)
{
    _menu = menu;
    //this->notify(new ::Input(KEY_UP), KEY_PRESSED);
    while vector
    {
    _newgame.setTexture(_tassets);
    _newgame.setTextureRect(sf::IntRect(0, 8, 566, 100));
    _newgame.setScale(0.5f, 0.5f);
    _newgame.setPosition(600, 330);
    }
}*/

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
