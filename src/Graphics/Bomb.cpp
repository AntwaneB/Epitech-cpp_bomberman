#include "Graphics/Bomb.hh"

Graphics::Bomb::Bomb(const ::Bomb* bomb, gdl::Model* model)
	: Object(bomb->position()), _bomb(bomb), _model(model)
{
 	scale(glm::vec3(0.002, 0.002, 0.002));
	translate(glm::vec3(0, 1, 0));

}

Graphics::Bomb::~Bomb()
{

}

bool
Graphics::Bomb::operator==(const ::Bomb* other) const
{
	return (other == _bomb);
}

bool
Graphics::Bomb::initialize()
{
    _model->setCurrentAnim(0);
    return (true);
}

void
Graphics::Bomb::update(gdl::Clock const &clock, gdl::Input &input)
{
	if (_bomb->progress() <= 20 || (_bomb->progress() > 40 && _bomb->progress() <= 60) || (_bomb->progress() > 80 && _bomb->progress() <= 100))
	 	scale(glm::vec3(1.025, 1.025, 1.025));
	else
	 	scale(glm::vec3(0.975, 0.975, 0.975));

	(void)clock;
	(void)input;
}

void
Graphics::Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	shader.bind();
	shader.setUniform("color", glm::vec4(1, 1, 1, 1));
	_model->draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
