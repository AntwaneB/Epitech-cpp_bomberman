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
#include "SdlContext.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BasicShader.hh"
#include "Clock.hh"
#include "Input.hh"
#include "Graphics/Player.hh"
#include "Graphics/Object.hh"
#include "Graphics/Cube.hh"
#include "Graphics/Character.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "Config.hpp"
#include <vector>

namespace Graphics
{

	class Level : public EventHandler<Graphics::Level>, public Subject, public gdl::Game
	{
	public:
		Level();
		Level(const ::Level*);
		virtual ~Level();

		virtual bool initialize();
		virtual bool update();
		virtual void draw();

	protected:
		const ::Level*	_level;
		gdl::SdlContext _context;
		gdl::BasicShader _shader;
		std::vector<Player> _players;
		std::vector<Graphics::Character*>	_characters;
	};

}

#endif	/* LEVEL_HH */
