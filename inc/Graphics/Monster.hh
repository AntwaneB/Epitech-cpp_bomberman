#ifndef	MONSTER_HPP_
# define	MONSTER_HPP_

#include <iostream>
#include <string>
#include "Model.hh"
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Position.hh"
#include "Core/Monster.hh"
#include "Core/Character.hh"

namespace Graphics
{
	class Monster : public Object
	{
	public:
      Monster(::Monster const *, gdl::Model*);
      virtual ~Monster();

      virtual bool  initialize();
      virtual void  update(gdl::Clock const &clock, gdl::Input &input);
      virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);

      int	getAngle(const::Character::Action);
      void  setAnim(bool);
      void  irotate(int);
	bool	operator==(const ::Monster*) const;

	private:
      gdl::Texture            _texture;
      const ::Monster*      _character;
      gdl::Model*             _model;
      int                     _frame = 0;
      bool                     _anim = false;
	};
};

#endif
