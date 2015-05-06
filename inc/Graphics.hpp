#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	class Map : public gdl::Game
	{
	public:
		Map();
		virtual ~Map();
		virtual bool	initialize();
		virtual bool	update();
		virtual bool	draw();
	};

	class Character
	{
	public:
		Character();
		virtual ~Character();
	};
};

#endif /* !GRAPHICS_HPP */