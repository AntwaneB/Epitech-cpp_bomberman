#ifndef GROUND_HH
#define	GROUND_HH

#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <ostream>
#include <string>

namespace Graphics
{

	class Ground : public Object
	{
		public:
			Ground(Position<double> const &);
			virtual ~Ground();

			virtual bool initialize();
			virtual void update(gdl::Clock const &clock, gdl::Input &input);
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

		private:
			gdl::Texture	_texture;
			gdl::Geometry	_geometry;
			float				_speed;

			int				_width;
			int				_height;
	};
};

#endif	/* GROUND_HH */