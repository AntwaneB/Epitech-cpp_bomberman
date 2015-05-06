/*
 * File:   Map.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:36 PM
 */

#ifndef MAP_HH
#define	MAP_HH

#include "SdlContext.hh"
#include "Game.hh"

namespace Graphics
{
	class Map : public gdl::Game
	{
	public:
		Map();
		virtual ~Map();
	private:
		gdl::SdlContext	_context;		
	};

	class Character
	{
	public:
		Character();
		virtual ~Character();
	};
};


#endif	/* MAP_HH */

