#ifndef OBJECT_HH
#define	OBJECT_HH

#include "SdlContext.hh"
#include "Game.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BasicShader.hh"
#include "Clock.hh"
#include "Input.hh"
#include "Position.hpp"
#include "Character.hpp"

namespace Graphics
{

	class Object
	{
	public:
		Object(Position const &);
		virtual ~Object();

		virtual bool initialize();
		virtual void update(gdl::Clock const &clock, gdl::Input &input);
		virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;

		void translate(glm::vec3 const &v);
		void translate(Position const &v);
		void rotate(glm::vec3 const& axis, float angle);
		void scale(glm::vec3 const& scale);
		glm::mat4 getTransformation();
		bool isLive(::Character* character);

	protected:
		Position		_position;
		glm::vec3	_rotation;
		glm::vec3	_scale;
	};

};


#endif	/* OBJECT_HH */