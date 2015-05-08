#ifndef CUBE_HH
#define	CUBE_HH

#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <ostream>

namespace Graphics
{

	class Cube : public Object
	{
		public:
			Cube();
			Cube(int, int, int);
			virtual ~Cube();
			virtual bool initialize();
			virtual void update(gdl::Clock const &clock, gdl::Input &input);
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);
		private:
			gdl::Texture _texture;
			gdl::Geometry _geometry;
			float _speed;
	};
};

#endif	/* CUBE_HH */