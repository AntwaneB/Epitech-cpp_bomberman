/*
 * File:   Display.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 4:07 PM
 */

#ifndef DISPLAY_HH
#define	DISPLAY_HH

#include "Observer.hpp"
#include "SdlContext.hh"
#include "Game.hh"

#include "Graphics/Level.hh"
#include "Graphics/Menu.hh"

namespace Graphics
{

	class Display : public EventHandler<Display>, public Subject
	{
	public:
		Display();
		virtual ~Display();

	private:
		void	runMenu(Subject* entity);
		void	updateMenu(Subject* entity);

		void	runLevel(Subject* entity);
		void	updateLevel(Subject* entity);

		void	exitGame(Subject* entity);

	private:
		Graphics::Level*	_level;
		Graphics::Menu*		_menu;
	};

}

#endif	/* DISPLAY_HH */
