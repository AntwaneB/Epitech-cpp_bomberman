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
		_splits.push_back(new Split(level));
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
	for (size_t i = 0; i < _splits.size(); i++)
		_splits[i]->initialize();
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
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	for (size_t i = 0; i < _splits.size(); i++)
		_splits[i]->update(_clock, _input);
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

