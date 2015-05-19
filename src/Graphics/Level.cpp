/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 8, 2015, 2:05 PM
 */

#include "Graphics/Level.hh"

Graphics::Level::Level(::Level const * level)
	: _level(level)
{
	for (size_t i = 0; i < 2; i++)
		_players.push_back(Player());
	_context.start(1920, 1080, "My bomberman!");
	this->initialize();
}

Graphics::Level::~Level()
{
	for (size_t j = 0; j < _players.size(); j++)
	{
		for (size_t i = 0; i < _players[j]._objects.size(); ++i)
			delete _players[j]._objects[i];
	}
}

bool
Graphics::Level::initialize()
{
	glEnable(GL_DEPTH_TEST);
	std::cout << _players.size() << std::endl;
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (!_players[i]._shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER)
			|| !_players[i]._shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER)
			|| !_players[i]._shader.build())
			return false;

		glm::mat4 projection = glm::perspective(13.0f, 960.0f / 1080.0f, 0.1f, 100.0f);
		glm::mat4 transformation = glm::lookAt(glm::vec3(0, 90, 0), glm::vec3(7, 0, 7), glm::vec3(0, 1, 0));

		_players[i]._shader.bind();
		_players[i]._shader.setUniform("view", transformation);
		_players[i]._shader.setUniform("projection", projection);

		_players[i]._map.initialize(&_players[i]._objects, _level->map().height(), _level->map().width(), _level->map().map());

		/*for (auto it = _level->characters().begin(); it != _level->characters().end(); ++it)
			{
				for (auto iit = it->second.begin(); iit != it->second.end(); ++iit)
				{
					Object* character = new Graphics::Character((*iit)->position(), *iit);
					character->initialize();
					_players[i]._objects.push_back(character);
				}
			}*/
	}

	return (true);
}

bool
Graphics::Level::update()
{
	for (size_t j = 0; j < _players.size(); j++)
	{
		_players[j]._map.update(&_players[j]._objects, _level->map().height(), _level->map().width(), _level->map().map());
		if (_players[j]._input.getKey(SDLK_ESCAPE) || _players[j]._input.getInput(SDL_QUIT))
		{
			_context.stop();
			this->notify(this, EXIT_TRIGGERED);
		}
		_context.updateClock(_players[j]._clock);
		_context.updateInputs(_players[j]._input);
		for (size_t i = 0; i < _players[j]._objects.size(); ++i)
		{
			if (_players[j]._objects[i] != NULL)
				_players[j]._objects[i]->update(_players[j]._clock, _players[j]._input);
		}
	}
	return (true);
}

void
Graphics::Level::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	size_t blocksPerLine = ceil(sqrt(_players.size()));
	size_t lines = floor(sqrt(_players.size()));
	size_t blockWidth = 1920 / blocksPerLine;
	size_t blockHeight = 1080 / lines;
	size_t x = 0;
	size_t y = 0;
	for (size_t j = 0; j < _players.size(); j++)
	{
		_players[j]._shader.bind();
		glViewport(x, y, blockWidth, blockHeight);
		//std::cout << x << " " << y << " "<< x + blockWidth << " " << y + blockHeight << std::endl;
		for (size_t i = 0; i < _players[j]._objects.size(); ++i)
			if (_players[j]._objects[i] != NULL)
				_players[j]._objects[i]->draw(_players[j]._shader, _players[j]._clock);
		x += blockWidth;
		if (x > 1920 - blockWidth)
		{
			x = 0;
			y += blockHeight;
		}
			/*if (y > 1080 - blockHeight)
			{
				std::cout << "ERROR" << std::endl;
				_context.stop();
			}*/
	}
	//std::cout << "FIN" << std::endl;
	_context.flush();
}

