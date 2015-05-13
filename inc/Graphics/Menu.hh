/*
 * File:   Menu.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 9:20 PM
 */

#ifndef MENU_HH
#define	MENU_HH

#include "Observer.hpp"
#include "SdlContext.hh"
#include "Game.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Menu
	{
	public:
		Menu();
		virtual ~Menu();
		void	update(int, int);

	private:
		sf::RenderWindow	_window;
		sf::Text 		_txt;
		sf::Texture		_tBackground;
		sf::Texture		_tArrow;
		sf::Sprite		_background;
		sf::Sprite		_arrow;		

	};
};
#endif	/* MENU_HH */
