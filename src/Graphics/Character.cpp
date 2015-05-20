#include "Graphics/Character.hh"

Graphics::Character::Character(Position const & position, ::Character const * character, gdl::Model* model)
	: Object(position), _character(character), _model(model), _position(Position(position.x(), position.y(), position.z()))
{
	scale(glm::vec3(0.0025, 0.0025, 0.0025));
}

Graphics::Character::~Character()
{

}

bool
Graphics::Character::initialize()
{
	_model->setCurrentAnim(0);
	return (true);
}

bool
Graphics::Character::isLive(::Character* character)
{
	if (character != _character)
		return (false);
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
	(void)clock;
	//_position = _character->position();
	if (_character->position().y() != _position.y() || _character->position().x() != _position.x())
	{
		int x = _character->position().x() - _position.x();
		int y = _character->position().y() - _position.y();
		translate(glm::vec3(x, 0, y));
		_position = _character->position();
	}
	if (input.getKey(SDLK_DOWN))
	{
		translate(glm::vec3(0, 0, -1));
		//rotate(glm::vec3(0, 0, -1), getAngle(DOWN));
	}
	if (input.getKey(SDLK_UP))
	{
		translate(glm::vec3(0, 0, 1));
		//rotate(glm::vec3(0, 0, 1), getAngle(UP));
	}
	if (input.getKey(SDLK_RIGHT))
	{
		translate(glm::vec3(-1, 0, 0));
		//rotate(glm::vec3(-1, 0, 0), getAngle(RIGHT));
	}
	if (input.getKey(SDLK_LEFT))
	{
		translate(glm::vec3(1, 0, 0));
		//rotate(glm::vec3(1, 0, 0), getAngle(LEFT));
	}
	/*
	if (input.getKey(SDLK_DOWN) || input.getKey(SDLK_UP) || input.getKey(SDLK_RIGHT) || input.getKey(SDLK_LEFT))
		_model->setCurrentAnim(0);
		_model->setCurrentAnim(1);
	*/
}

void
Graphics::Character::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model->draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
