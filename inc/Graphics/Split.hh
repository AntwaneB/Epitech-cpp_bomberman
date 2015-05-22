#ifndef SPLIT_HH
#define SPLIT_HH

#include <list>
#include "Input.hh"
#include "Graphics/Object.hh"
#include "Graphics/Character.hh"
#include "Graphics/Bomb.hh"
#include "Graphics/Item.hh"
#include "Graphics/Map.hh"
#include "Graphics/Cube.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "Config.hpp"
#include "Level.hpp"
#include "Character.hpp"

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
		const ::Level*							_level;
		gdl::BasicShader						_shader;
		const ::Character*					_player;
		std::list<Graphics::Character*>	_characters;
		std::list<Graphics::Bomb*>			_bombs;
		std::list<Graphics::Item*>		_items;
		Graphics::Map*							_map;
		gdl::Model*								_model;
	};

};

#endif	/* SPLIT_HH */