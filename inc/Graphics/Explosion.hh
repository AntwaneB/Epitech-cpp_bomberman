#ifndef EXPLOSION_HH
#define	EXPLOSION_HH

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

	class Explosion : public Object
	{
		public:
			Explosion(Position<> const &, gdl::Texture*);
			virtual ~Explosion();

			virtual bool initialize();
			virtual void update(gdl::Clock const &clock, gdl::Input &input);
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

		private:
			gdl::Geometry	_geometry;
			gdl::Texture*	_texture;
	};
};

#endif	/* EXPLOSION_HH */