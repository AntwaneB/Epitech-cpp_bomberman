#include "Graphics/Character.hh"

Graphics::Character::Character(Position const & position, ::Character const * character)
	: Object(position), _character(character)
{
	scale(glm::vec3(0.0025, 0.0025, 0.0025));
}

Graphics::Character::~Character()
{

}

bool Graphics::Character::initialize()
{
	_speed = 50.0f;

    if (_model.load("./libgdl/assets/marvin.fbx") == false)
      {
	     std::cout << "Cannot load the marvin model" << std::endl;
	     return (false);
      }
    _model.setCurrentAnim(0);
    return (true);
}

void Graphics::Character::update(gdl::Clock const &clock, gdl::Input &input)
{
	_position = _character->position();

	if (input.getKey(SDLK_UP))
		translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
	if (input.getKey(SDLK_DOWN))
		translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
	if (input.getKey(SDLK_LEFT))
		translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
	if (input.getKey(SDLK_RIGHT))
		translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void Graphics::Character::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model.draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
