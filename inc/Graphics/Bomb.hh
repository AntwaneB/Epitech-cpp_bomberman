#ifndef		Bomb_HPP_
# define	Bomb_HPP_

#include "Model.hh"
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <string>

namespace Graphics
{
	class Bomb : public Object
	{
	public:
		Bomb(Position const &);
		virtual ~Bomb();

		virtual bool  initialize();
		virtual void  update(gdl::Clock const &clock, gdl::Input &input);
		virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);

	private:
		gdl::Texture	_texture;
		gdl::Model		_model;
	};
};

#endif