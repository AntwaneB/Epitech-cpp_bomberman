#include "Graphics/Split.hh"

Graphics::Split::Split(::Level const * level)
	: _level(level), _model(new gdl::Model)
{
	_map = new Map(level->map());
}

Graphics::Split::~Split()
{
	delete _map;
	for (size_t i = 0; i < _characters.size(); ++i)
		delete _characters[i];
}

bool Graphics::Split::initialize()
{
	if (!_shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER)
	|| !_shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER)
	|| !_shader.build())
		return false;

	glm::mat4 projection = glm::perspective(13.0f, 960.0f / 1080.0f, 0.1f, 100.0f);
	glm::mat4 transformation = glm::lookAt(glm::vec3(0, 90, 0), glm::vec3(7, 0, 7), glm::vec3(0, 1, 0));

	_shader.bind();
	_shader.setUniform("view", transformation);
	_shader.setUniform("projection", projection);

	_map->initialize();

	gdl::Model* model = new gdl::Model;
	if (model->load("./libgdl/assets/marvin.fbx") == false || _model->load("./libgdl/assets/bomb.fbx") == false)
	{
		std::cout << "Cannot load the marvin model" << std::endl;
		return (false);
	}
	for (auto it = _level->characters().begin(); it != _level->characters().end(); ++it)
	{
		for (auto iit = it->second.begin(); iit != it->second.end(); ++iit)
		{
			Object* character = new Graphics::Character((*iit)->position(), *iit, model);
			character->initialize();
			_characters.push_back(character);
		}
	}
	return (true);
}

void Graphics::Split::update(gdl::Clock clock, gdl::Input input)
{
	_map->update();
	if (_bombs.size() != _level->bombs().size())
	{
		for (auto it=_level->bombs().begin(); it != _level->bombs().end(); ++it)
		{
			Object* bomb = new Graphics::Bomb(it->first, _model);
			bomb->initialize();
			_bombs.push_back(bomb);
		}
	}

	auto characters = _level->charactersRaw();
	for (size_t i = 0; i < _characters.size(); ++i)
	{
		if (_characters[i] != NULL)
		{
			if (_characters[i]->isLive(characters[i]) == false)
			{
				std::cout << "Character[" << i << "] is dead" << std::endl;
				delete _characters[i];
				_characters[i] = NULL;
			}
			_characters[i]->update(clock, input);
		}
	}
}

void Graphics::Split::draw(gdl::Clock clock)
{
	_shader.bind();
	_map->draw(_shader, clock);
	for (size_t i = 0; i < _characters.size(); ++i)
		if (_characters[i] != NULL)
			_characters[i]->draw(_shader, clock);
	if (_bombs.size() > 0)
		for (size_t i = 0; i < _bombs.size(); ++i)
			_bombs[i]->draw(_shader, clock);
}