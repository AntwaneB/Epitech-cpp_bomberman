#ifndef	CHARACTER_HPP_
# define	CHARACTER_HPP_

#include <iostream>
#include <string>
#include "Model.hh"
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Position.hpp"
#include "Character.hpp"

namespace Graphics
{
	class Character : public Object
	{
   public:
      enum direction {UP, LEFT, DOWN, RIGHT};
      Character(Position const &, ::Character const *);
      virtual ~Character();

      virtual bool  initialize();
      virtual void  update(gdl::Clock const &clock, gdl::Input &input);
      virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);
      int getAngle(direction);

	private:
		float				_speed;

      gdl::Texture	_texture;
      gdl::Model		_model;
      direction _pos = UP;

		const ::Character* _character;
	};
};

#endif
