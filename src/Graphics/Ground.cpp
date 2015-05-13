#include "Graphics/Ground.hh"
#include <iostream>

Graphics::Ground::Ground()
{

}

Graphics::Ground::Ground(double x, double y, double z, int type) : _type(type), _width((x * 2) + 1), _height((y * 2) + 1)
{
	position(x, y, z);
}

Graphics::Ground::~Ground()
{

}

bool Graphics::Ground::initialize()
{
	std::string path;
	_speed = 10.0f;
	if (_type == 0)
		path = "./libgdl/assets/sand.tga";
	if(_texture.load(path) == false)
	{
		std::cout << "false texture" << std::endl;
		return (false);
	}
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.5, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.5, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.5, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.5, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, -0.5 * _height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.5, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.5, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.5, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.5, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, -0.5 * _height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.5, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.5, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, -0.5 * _height));
	_geometry.pushVertex(glm::vec3(0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, 0.5 * _height));
	_geometry.pushVertex(glm::vec3(-0.5 * _width, 0.4, -0.5 * _height));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.build();
	return (true);
}

void Graphics::Ground::update(gdl::Clock const &clock, gdl::Input &input)
{
	if (input.getKey(SDLK_UP))
		translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
	if (input.getKey(SDLK_DOWN))
		translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
	if (input.getKey(SDLK_LEFT))
		translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
	if (input.getKey(SDLK_RIGHT))
		translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void Graphics::Ground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}