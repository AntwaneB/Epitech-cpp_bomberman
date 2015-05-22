#include "Graphics/Bomb.hh"

Graphics::Bomb::Bomb(Position const & position, gdl::Model* model)
	: Object(position), _model(model)
{
	rotate(glm::vec3(1, 0, 0), -90);
	_position = Position(position.x(), position.y(), position.z());
 	scale(glm::vec3(0.0025, 0.0025, 0.0025));
}

Graphics::Bomb::~Bomb()
{

}

bool		Graphics::Bomb::initialize()
{
    _model->setCurrentAnim(0);
    return (true);
}

void Graphics::Bomb::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)clock;
	(void)input;
}

void Graphics::Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model->draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
