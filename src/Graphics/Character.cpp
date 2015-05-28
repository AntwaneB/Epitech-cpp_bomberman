#include "Graphics/Character.hh"

Graphics::Character::Character(::Character const * character, gdl::Model* model)
	: Object(character->position()), _character(character), _model(model)
{
	_position.decX(0.5);
	_position.decY(0.5);
	scale(glm::vec3(0.0025, 0.0025, 0.0025));
}

Graphics::Character::~Character()
{

}

bool
Graphics::Character::initialize()
{
	_model->createSubAnim(0, "RESET", 0, 0);
  	_model->createSubAnim(0, "START", 20, 30);
  	_model->createSubAnim(0, "RUN", 37, 53);
  	_model->createSubAnim(0, "END", 54, 100);
	return (true);
}

bool
Graphics::Character::operator==(const ::Character* other) const
{
	return (other == _character);
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
	(void)input;
	//_position = _character->position();
	if (_character->position().y() != _position.y() || _character->position().x() != _position.x())
	{
		//double x = _character->position().x() - _position.x();
		//double y = _character->position().y() - _position.y();
		//translate(glm::vec3(x, 0, y));
		/*glm::vec3 position;
		position[0] = _character->position().x();
		position[1] = _character->position().z();
		position[2] = _character->position().y();*/
		_position = _character->position();
		_position.decX(0.5);
		_position.decY(0.5);
	}
	setAnim(_character->moving());
}

void
Graphics::Character::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model->draw(shader, getTransformation(), GL_QUADS);
	if (_anim == true)
	{
		if (_frame == 20 || _frame > 45)
		{
			if (_frame > 45)
				_frame = 21;
			_model->setCurrentSubAnim("START");
		}
		if (_frame == 30)
			_model->setCurrentSubAnim("RUN");
		if (_frame == 45)
			_frame = 30;
		_frame += 1;
	}
    if (_anim == false)
    {
		if (_frame > 20 && _frame < 46)
		{
			_model->setCurrentSubAnim("END");
			_frame = 46;
		}
		if (_frame >= 46 && _frame <= 93)
			_frame += 1;
		if (_frame >= 93)
		{
			_model->setCurrentSubAnim("RESET");
			_frame = 20;
		}
		if (_frame != 20)
			_frame += 1;
	}
	(void)clock;
}

void Graphics::Character::setAnim(bool anim)
{
	_anim = anim;
}