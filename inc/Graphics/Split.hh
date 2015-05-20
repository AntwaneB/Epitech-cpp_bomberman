#ifndef SPLIT_HH
#define SPLIT_HH

#include "Input.hh"
#include "Graphics/Object.hh"
#include "Graphics/Character.hh"
#include "Graphics/Bomb.hh"
#include "Graphics/Map.hh"
#include "Graphics/Cube.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "Config.hpp"
#include "Level.hpp"
#include <vector>

namespace Graphics
{

	class Split
	{
	public:
		Split(const ::Level*);
		virtual ~Split();

		virtual bool initialize();
		virtual void update(gdl::Clock, gdl::Input);
		virtual void draw(gdl::Clock);

	public:
		const ::Level*			_level;
		gdl::BasicShader 		_shader;
		const ::Character*		_player;
		std::vector<Graphics::Object*>		_ocharacters;
		std::vector<const ::Character*>		_characters;
		std::vector<Graphics::Object*>		_bombs;
		//std::vector<Graphics::Item*>		_items;
		Graphics::Map*						_map;
	};

};

#endif	/* SPLIT_HH */