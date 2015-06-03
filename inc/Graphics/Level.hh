/*
 * File:   Level.hh
 * Author: buchse_a
 *
 * Created on May 8, 2015, 2:05 PM
 */

#ifndef LEVEL_HH
#define	LEVEL_HH

#include "Game.hh"
#include "Core/Observer.hpp"
#include "Core/Level.hh"
#include "SdlContext.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BasicShader.hh"
#include "Clock.hh"
#include "Input.hh"
#include "Graphics/Split.hh"
#include "Graphics/Object.hh"
#include "Graphics/Cube.hh"
#include "Graphics/Character.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "Core/Config.hh"
#include "Core/Input.hh"
#include <vector>

namespace Graphics
{

	class Level : public EventHandler<Graphics::Level>, public Subject, public gdl::Game
	{
	public:
		Level(const ::Level*);
		virtual ~Level();

		virtual bool initialize();
		virtual bool update();
		virtual bool updateInput();
		virtual void draw();

	protected:
		const ::Level*						_level;
		gdl::SdlContext					_context;
		gdl::Input							_input;
		gdl::Clock							_clock;
		std::vector<gdl::Model*> 		_models;
		std::vector<Graphics::Split*> _splits;
		size_t								_size;
	};

}

#endif	/* LEVEL_HH */
