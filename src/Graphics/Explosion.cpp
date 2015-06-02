#include "Graphics/Explosion.hh"
#include <iostream>

Graphics::Explosion::Explosion(Position<> const & position, gdl::Texture* texture)
	: Object(position), _texture(texture)
{
}

Graphics::Explosion::~Explosion()
{

}

bool Graphics::Explosion::initialize()
{
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
	_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
	_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
	_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
	_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
	_geometry.pushUv(glm::vec2(0.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 0.0f));
	_geometry.pushUv(glm::vec2(1.0f, 1.0f));
	_geometry.pushUv(glm::vec2(0.0f, 1.0f));
	_geometry.build();
	return (true);
}

void Graphics::Explosion::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)input;
	(void)clock;
}

void Graphics::Explosion::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	(void)clock;
	_texture->bind();
	_geometry.draw(shader, getTransformation(), GL_QUADS);
}
