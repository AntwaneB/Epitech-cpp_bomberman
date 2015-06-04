#include <iostream>
#include "Graphics/Skybox.hh"
#include "global.hh"

Graphics::Skybox::Skybox()
	: Object(Position<double>(-1,-1, -1))
{
	_width  = 45;
	_height = 40;
}

Graphics::Skybox::~Skybox()
{

}

bool Graphics::Skybox::initialize()
{
	if(_texture.load("./assets/textures/skybox.tga") == false)
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

void Graphics::Skybox::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)input;
	(void)clock;
}

void Graphics::Skybox::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture.bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}