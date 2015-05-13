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
	this->initialize();
	while (this->update() == true)
		this->draw();
}

Graphics::Level::~Level()
{
	for (size_t i = 0; i < _objects.size(); ++i)
		delete _objects[i];
}

bool
Graphics::Level::initialize()
{
	if (!_context.start(1920, 1080, "My bomberman!"))
		return false;
	glEnable(GL_DEPTH_TEST);
	if (!_shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER)
	|| !_shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER)
	|| !_shader.build())
		return false;
	glm::mat4 projection;
	glm::mat4 transformation;
	glViewport(1920/2, 0, 1920/2, 1080);
	projection = glm::perspective(60.0f, 960.0f / 1080.0f, 0.1f, 100.0f);
	transformation = glm::lookAt(glm::vec3(0, 7, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_shader.bind();
	_shader.setUniform("view", transformation);
	_shader.setUniform("projection", projection);
	_map.initialize(&_objects, _level->map().height(), _level->map().width(), _level->map().getMap());
	return (true);
}

bool
Graphics::Level::update()
{
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		return false;
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	for (size_t i = 0; i < _objects.size(); ++i)
	_objects[i]->update(_clock, _input);
	return (true);
}

void
Graphics::Level::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.bind();
	for (size_t i = 0; i < _objects.size(); ++i)
	_objects[i]->draw(_shader, _clock);
	_context.flush();
}
