/*
 * File:   Level.cpp
 * Author: buchse_a
 *
 * Created on May 8, 2015, 2:05 PM
 */

#include "Graphics/Level.hh"
#include "Core/Input.hh"

Graphics::Level::Level(::Level const * level)
	: _level(level)
{
	for (size_t i = 0; i < 6; i++)
		_splits.push_back(new Split(level, i));
	_context.start(1920, 1080, "My bomberman!");
	this->initialize();
}

Graphics::Level::~Level()
{
	for (size_t i = 0; i < _splits.size(); i++)
		delete _splits[i];
}

bool
Graphics::Level::initialize()
{
	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i < 5; i++)
		_models.push_back(new gdl::Model);
	if (_models[0]->load("./libgdl/assets/marvin.fbx") == false
		|| _models[1]->load("./libgdl/assets/a bomb/a_bomb.fbx") == false
		|| _models[2]->load("./libgdl/assets/ball_01.fbx") == false
		|| _models[3]->load("./libgdl/assets/ball_02.fbx") == false
		|| _models[4]->load("./libgdl/assets/ball_03.fbx") == false)
	{
		std::cout << "Cannot load model" << std::endl;
		return (false);
	}
	for (size_t i = 0; i < _splits.size(); i++)
		_splits[i]->initialize(_models);
	return (true);
}

bool
Graphics::Level::update()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
	{
		_context.stop();
		this->notify(this, EXIT_TRIGGERED);
	}
	else
	{
		std::map<int, Input::Key> keys;
		keys[SDLK_DOWN] = ::Input::P1_DOWN;
		keys[SDLK_UP] = ::Input::P1_UP;
		keys[SDLK_RIGHT] = ::Input::P1_RIGHT;
		keys[SDLK_LEFT] = ::Input::P1_LEFT;
		keys[SDLK_KP_0] = ::Input::P1_SPACE;
		keys[SDLK_z] = ::Input::P2_UP;
		keys[SDLK_s] = ::Input::P2_DOWN;
		keys[SDLK_q] = ::Input::P2_LEFT;
		keys[SDLK_d] = ::Input::P2_RIGHT;
		keys[SDLK_SPACE] = ::Input::P2_SPACE;

		keys[SDLK_p] = ::Input::PAUSE;

		for (auto key = keys.begin(); key != keys.end(); ++key)
		{
			if (_input.getKey((*key).first))
				this->notify(new Input((*key).second), KEY_PRESSED);
		}
	}

	for (size_t i = 0; i < _splits.size(); i++)
		_splits[i]->update(_clock, _input);

	_context.updateClock(_clock);
	_context.updateInputs(_input);

	return (true);
}

bool
Graphics::Level::updateInput()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
	{
		_context.stop();
		this->notify(this, EXIT_TRIGGERED);
	}
	else
	{
		std::map<int, Input::Key> keys;
		keys[SDLK_p] = ::Input::PAUSE;

		for (auto key = keys.begin(); key != keys.end(); ++key)
		{
			if (_input.getKey((*key).first))
				this->notify(new Input((*key).second), KEY_PRESSED);
		}
	}

	_context.updateInputs(_input);

	return (true);
}

void
Graphics::Level::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	size_t blocksPerLine = ceil(sqrt(_splits.size()));
	size_t lines = floor(sqrt(_splits.size()));

	size_t blockWidth = 1920 / blocksPerLine;
	size_t blockHeight = 1080 / lines;

	size_t x = 0;
	size_t y = 0;
	for (size_t i = 0; i < _splits.size(); i++)
	{
		glViewport(x, y, blockWidth, blockHeight);
		_splits[i]->moveCamera();
		_splits[i]->draw(_clock);
		x += blockWidth;
		if (x > 1920 - blockWidth)
		{
			x = 0;
			y += blockHeight;
		}
	}

	_context.flush();
}

