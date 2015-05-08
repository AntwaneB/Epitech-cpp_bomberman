/*
 * File:   Level.hh
 * Author: buchse_a
 *
 * Created on May 8, 2015, 2:05 PM
 */

#ifndef LEVEL_HH
#define	LEVEL_HH

#include "Game.hh"
#include "Observer.hpp"
#include "Level.hpp"

namespace Graphics
{

	class Level : public EventHandler<Graphics::Level>, public gdl::Game
	{
	public:
		Level(const ::Level*);
		virtual ~Level();

		virtual bool initialize();
		virtual bool update();
		virtual void draw();

	private:
		const ::Level*	_level;
	};

}

#endif	/* LEVEL_HH */
