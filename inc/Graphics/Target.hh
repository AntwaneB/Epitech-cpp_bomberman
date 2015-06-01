#ifndef TARGET_HH
#define	TARGET_HH

#include <ostream>
#include <string>
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "Core/Position.hh"
#include "Core/Block.hh"

namespace Graphics
{

	class Target : public Object
	{
		public:
			Target(Position<> const &, Block const *, gdl::Texture*);
			virtual ~Target();

			virtual bool initialize();
			virtual void update(gdl::Clock const &clock, gdl::Input &input);
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

		private:
			gdl::Geometry	_geometry;

			const Block*	_block;
			gdl::Texture*	_texture;
	};
};

#endif	/* TARGET_HH */