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

/*
	Besoin du chemin du fichier pour la texture
	position de l'image dans l'asset
	de la position du sprite dans la scene
*/


namespace Graphics
{
	class Menu
	{
	public:
		Menu();
		virtual ~Menu();
		void	NewGame();
		void	update(int, int);

	private:
		sf::RenderWindow	_window;

		::Menu*				_menu;

		//Textures
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

	};
};
#endif	/* MENU_HH */
