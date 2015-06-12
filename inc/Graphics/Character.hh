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
      Character(::Character const *, gdl::Model*, const size_t, const size_t);
      virtual ~Character();

      virtual bool  initialize();
      virtual void  update(gdl::Clock const &clock, gdl::Input &input);
      virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);

      int	getAngle(const::Character::Action);
      void  setAnim(bool);
      void  irotate(int);
	bool	operator==(const ::Character*) const;

	private:
      gdl::Texture            _texture;
      const ::Character*      _character;
      gdl::Model*             _model;
      glm::vec4               _color;
      int                     _frame;
      bool                    _anim;
      size_t                  _id;
      size_t                  _charactersCount;
	};
};

#endif
