#include "Graphics/Character.hh"

Graphics::Character::Character(Position const & position, ::Character const * character)
	: Object(position), _character(character)
{
	scale(glm::vec3(0.0025, 0.0025, 0.0025));
}

Graphics::Character::~Character()
{

}

bool
Graphics::Character::initialize()
{
	_speed = 10.0f;

	if (_model.load("./libgdl/assets/micro_dragon.fbx") == false)
	{
		std::cout << "Cannot load the marvin model" << std::endl;
		return (false);
	}
	_model.setCurrentAnim(0);
	return (true);
}

int 
Graphics::Character::getAngle(direction key)
{
	switch(_pos)
	{
		case UP:
			switch(key)
			{
				case UP:
					return (0);
				case DOWN:
					return (180);
				case LEFT:
					return (-90);
				case RIGHT:
					return (90);
			}
		case DOWN:
			switch(key)
			{
				case UP:
					return (180);
				case DOWN:
					return (0);
				case LEFT:
					return (90);
				case RIGHT:
					return (-90);
			}
		case LEFT:
			switch(key)
			{
				case UP:
					return (90);
				case DOWN:
					return (-90);
				case LEFT:
					return (0);
				case RIGHT:
					return (180);
			}
		case RIGHT:
			switch(key)
			{
				case UP:
					return (-90);
				case DOWN:
					return (90);
				case LEFT:
					return (180);
				case RIGHT:
					return (0);
			}
	}
	return (0);
}

void
Graphics::Character::update(gdl::Clock const &clock, gdl::Input &input)
{
	//_position = _character->position();

	if (input.getKey(SDLK_DOWN))
	{
		translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
		//rotate(glm::vec3(0, 0, -1), getAngle(DOWN));
	}
	if (input.getKey(SDLK_UP))
	{
		translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
		//rotate(glm::vec3(0, 0, 1), getAngle(UP));
	}
	if (input.getKey(SDLK_RIGHT))
	{
		translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
		//rotate(glm::vec3(-1, 0, 0), getAngle(RIGHT));
	}
	if (input.getKey(SDLK_LEFT))
	{
		translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
		//rotate(glm::vec3(1, 0, 0), getAngle(LEFT));
	}
	/*
	if (input.getKey(SDLK_DOWN) || input.getKey(SDLK_UP) || input.getKey(SDLK_RIGHT) || input.getKey(SDLK_LEFT))
		_model.setCurrentAnim(0);
		_model.setCurrentAnim(1);
	*/
}

void
Graphics::Character::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model.draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
