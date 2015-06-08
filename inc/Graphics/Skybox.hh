#ifndef SKYBOX_HH
#define	SKYBOX_HH

#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <ostream>
#include <string>

namespace Graphics
{

	class Skybox : public Object
	{
		public:
			Skybox();
			virtual ~Skybox();

			virtual bool initialize();
			virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

		private:
			gdl::Texture	_texture;
			gdl::Geometry	_geometry;
			float				_speed;

			int				_width;
			int				_height;
	};
};

#endif	/* SKYBOX_HH */