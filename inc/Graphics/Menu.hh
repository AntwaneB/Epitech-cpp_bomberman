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
#include <map>
#include "Core/Menu.hh"
#include "Core/Observer.hpp"
#include "SdlContext.hh"
#include "Game.hh"

namespace Graphics
{
	class Menu : public EventHandler<Graphics::Menu>, public Subject
	{
	public:
		Menu();
		virtual ~Menu();

		void	init(::Menu *);
		void	run();
		void	update();
		void	draw();

	private:
		sf::RenderWindow	_window;

		::Menu*			_menu;

		//Textures
		sf::Texture		_assetsTexture;
		sf::Texture		_backgroundTexture;

		//Sprite
		std::list<sf::Sprite>	_sprites;
		sf::Sprite					_background;
		sf::Sprite					_cursor;

		/*
		sf::Texture 	_tassets;
		sf::Texture		_tBackground;
		sf::Texture		_tSubBackground;

		//Sprite
		sf::Sprite		_background;
		sf::Sprite		_subBackground;
		sf::Sprite		_assets;
		sf::Sprite		_newgame;
		sf::Sprite		_loadgame;
		sf::Sprite		_setting;
		sf::Sprite		_exit;
		sf::Sprite		_quote;
		sf::Sprite		_rya;
		*/
	};
};
#endif	/* MENU_HH */
