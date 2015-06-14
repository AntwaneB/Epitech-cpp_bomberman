#include "Graphics/Monster.hh"

Graphics::Monster::Monster(::Monster const * monster, gdl::Model* model)
	: Object(monster->position()), _monster(monster), _model(model)
{
	_position.decX(0.5);
	_position.decY(0.5);
	scale(glm::vec3(0.005, 0.005, 0.005));
}

Graphics::Monster::~Monster()
{
}

bool
Graphics::Monster::initialize()
{
	_model->setCurrentAnim(0);
  	return (true);
}

bool
Graphics::Monster::operator==(const ::Monster* other) const
{
	return (other == _monster);
}

int
Graphics::Monster::getAngle(const::Character::Action key)
{
	switch(key)
		{
			case ::Character::Action::MOVE_UP:
				return (180);
			case ::Character::Action::MOVE_DOWN:
				return (0);
			case ::Character::Action::MOVE_LEFT:
				return (-90);
			case ::Character::Action::MOVE_RIGHT:
				return (90);
			default:
				return (0);
		}
	return (0);
}

void
Graphics::Monster::irotate(int angle)
{
	_rotation = glm::vec3(0, angle, 0);
	if (angle == 0)
		return;
	if (angle == 90)
		{
			double position = _position.x();
			_position.setX(_position.y() * -1 + 1);
			_position.setY(position);
		}
	else if (angle == -90)
		{
			double position = _position.x();
			_position.setX(_position.y());
			_position.setY(position * -1 + 1);
		}
	else
		{
			_position.setX(_position.x() * -1 + 1);
			_position.setY(_position.y() * -1 + 1);
		}
}

void
Graphics::Monster::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)clock;
	(void)input;

	if (_monster->position().y() != _position.y() || _monster->position().x() != _position.x())
	{
		_position = _monster->position();
		irotate(getAngle(_monster->direction()));
		_position.decX(0.5);
		_position.decY(0.5);
		_position.incZ(1.8);
	}
}

void
Graphics::Monster::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	shader.bind();
	shader.setUniform("color", glm::vec4(1,1,1,1));
	_model->draw(shader, getTransformation(), clock.getElapsed());
}