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
#include "Core/Position.hh"
#include "Core/Character.hh"

namespace Graphics
{
	class Character : public Object
	{
   public:
      enum direction {UP, LEFT, DOWN, RIGHT};

	public:
      Character(::Character const *, gdl::Model*);
      virtual ~Character();

      virtual bool  initialize();
      virtual void  update(gdl::Clock const &clock, gdl::Input &input);
      virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);

      int	getAngle(direction);
      void  setAnim(bool);
	bool	operator==(const ::Character*) const;

	private:
      gdl::Texture            _texture;
      direction               _pos = UP;
      const ::Character*      _character;
      gdl::Model*             _model;
      int                     _frame = 0;
      bool                     _anim = false;
	};
};

#endif
