#ifndef PLAYER_HH
#define PLAYER_HH

#include "Input.hh"
#include "Graphics/Object.hh"
#include "Graphics/Map.hh"
#include "Graphics/Cube.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "Config.hpp"
#include <vector>

namespace Graphics
{

	class Player
	{
	public:
		Player();
		virtual ~Player();
	public:
		gdl::SdlContext _context;
		gdl::Clock _clock;
		gdl::Input _input;
		gdl::BasicShader _shader;
		std::vector<Object*> _objects;
		Map	_map;
	};

};

#endif	/* PLAYER_HH */