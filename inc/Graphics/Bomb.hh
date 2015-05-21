#ifndef GRAPHICS_BOMB_HPP_
# define	GRAPHICS_BOMB_HPP_

#include <iostream>
#include <string>
#include "Model.hh"
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Bomb.hh"

namespace Graphics
{

	class Bomb : public Object
	{
	public:
		Bomb(const ::Bomb*, gdl::Model*);
		virtual ~Bomb();

		virtual bool  initialize();
		virtual void  update(gdl::Clock const &clock, gdl::Input &input);
		virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);

		bool	operator==(const ::Bomb*) const;

	private:
		const ::Bomb*	_bomb;
		gdl::Texture	_texture;
		gdl::Model*		_model;
	};

};

#endif
