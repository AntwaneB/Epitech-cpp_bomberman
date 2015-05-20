#include "Graphics/Object.hh"

Graphics::Object::Object(Position const & position)
	: _position(position), _rotation(0, 0, 0), _scale(1, 1, 1)
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
	(void)input;
	(void)clock;
}

bool Graphics::Object::isLive(::Character* character)
{
	return (true);
}

void Graphics::Object::translate(glm::vec3 const &v)
{
	_position = _position + Position(v[0], v[2], v[1]);
}

void Graphics::Object::translate(Position const &v)
{
	_position = _position + v;
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
	glm::vec3 position;
	position[0] = _position.x();
	position[1] = _position.z();
	position[2] = _position.y();

	glm::mat4 transform(1);
	transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, position);
	transform = glm::scale(transform, _scale);

	return (transform);
}
