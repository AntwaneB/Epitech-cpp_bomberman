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
			Cube(Position const &, Block const *, gdl::Texture*);
			virtual ~Cube();

			virtual bool initialize();
			virtual void update(gdl::Clock const &clock, gdl::Input &input);
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

		private:
			gdl::Geometry	_geometry;

			const Block*	_block;
			gdl::Texture*	_texture;
	};
};

#endif	/* CUBE_HH */