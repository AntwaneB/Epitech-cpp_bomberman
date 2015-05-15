#ifndef CUBE_HH
#define	CUBE_HH

#include <ostream>
#include <string>
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Position.hpp"
#include "Block.hh"

namespace Graphics
{

	class Cube : public Object
	{
		public:
			Cube(Position const &, Block const *);
			virtual ~Cube();

			virtual bool initialize();
			virtual void update(gdl::Clock const &clock, gdl::Input &input);
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

		private:
			gdl::Texture	_texture;
			gdl::Geometry	_geometry;
			float				_speed;

			const Block*	_block;
	};
};

#endif	/* CUBE_HH */