#include "Graphics/Object.hh"

Graphics::Object::Object()
{
	
}

Graphics::Object::~Object()
{

}

bool Graphics::Object::initialize()
{
	return (true);
}

void Graphics::Object::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)clock;
	(void)input;
}

void Graphics::Object::translate(glm::vec3 const &v)
{
	_position += v;
}

void Graphics::Object::rotate(glm::vec3 const& axis, float angle)
{
	_rotation += axis * angle;
}

void Graphics::Object::scale(glm::vec3 const& scale)
{
	_scale *= scale;
}

glm::mat4 Graphics::Object::getTransformation()
{
	glm::mat4 transform(1);
	transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, _position);
	transform = glm::scale(transform, _scale);
	return (transform);
}