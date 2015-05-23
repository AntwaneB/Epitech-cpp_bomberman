/*
 * File:   Map.hh
 * Author: buchse_a
 *
 * Created on May 6, 2015, 3:36 PM
 */

#ifndef MAP_HH
#define	MAP_HH

#include <vector>
#include "SdlContext.hh"
#include "Game.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BasicShader.hh"
#include "Clock.hh"
#include "Input.hh"
#include "Graphics/Object.hh"
#include "Graphics/Cube.hh"
#include "Graphics/Ground.hh"
#include "Graphics/Bomb.hh"
#include "Core/Block.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "Core/Map.hpp"

namespace Graphics
{

	class Map
	{
	public:
		Map(const ::Map&);
		virtual ~Map();

		virtual bool initialize();
		virtual bool update();
		virtual void draw(gdl::AShader&, gdl::Clock const&);

	private:
		const ::Map* _map;
		//std::vector<std::vector<::Block*> > _blocks;
		std::vector<std::vector<Graphics::Object*> > _blocks;
		Graphics::Object* _ground;
	};

};


#endif	/* MAP_HH */

