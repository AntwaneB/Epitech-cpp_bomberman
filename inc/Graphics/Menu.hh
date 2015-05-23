/*
 * File:   Menu.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 9:20 PM
 */

#ifndef MENU_HH
#define	MENU_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Core/Observer.hpp"
#include "SdlContext.hh"
#include "Game.hh"

namespace Graphics
{
	class Menu
	{
	public:
		Menu();
		virtual ~Menu();
		void	MainWin();
		void	update(int, int);

	private:
		sf::RenderWindow	_window;
		sf::Text 		_txt;
		sf::Texture		_tBackground;
		sf::Texture		_tArrow;
		sf::Sprite		_background;
		sf::Sprite		_arrow;

		//Textures
		sf::Texture 	_tassets;

		//Sprite
		sf::Sprite		_assets;
		sf::Sprite		_newgame;
		sf::Sprite		_loadgame;
		sf::Sprite		_setting;
		sf::Sprite		_exit;
		sf::Sprite		_quote;
		sf::Sprite		_rya;

	};
};
#endif	/* MENU_HH */
