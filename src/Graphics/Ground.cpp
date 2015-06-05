#include <iostream>
#include "Graphics/Ground.hh"
#include "global.hh"

Graphics::Ground::Ground(Position<double> const & position)
	: Object(position), _width((position.x() * 2) + 1), _height((position.y() * 2) + 1)
{
}

Graphics::Ground::~Ground()
{

}

bool Graphics::Ground::initialize()
{
	_speed = 50.0f;
	std::string path = g_settings["maps"]["floor_texture"];// "./assets/textures/sand.tga";
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
	(void)input;
	(void)clock;
}

void Graphics::Ground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	shader.bind();
	shader.setUniform("color", glm::vec4(1, 1, 1, 1));
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}