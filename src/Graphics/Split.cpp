#include "Graphics/Split.hh"

Graphics::Split::Split(::Level const * level)
	: _level(level)
{
	_map = new Map(level->map());
}

Graphics::Split::~Split()
{
	delete _map;
	for (size_t i = 0; i < _ocharacters.size(); ++i)
		delete _ocharacters[i];
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
	if (model->load("./libgdl/assets/marvin.fbx") == false)
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
			_ocharacters.push_back(character);
			_characters.push_back(*iit);
		}
	}
	return (true);
}

void Graphics::Split::update(gdl::Clock clock, gdl::Input input)
{
	_map->update();
	for (size_t i = 0; i < _ocharacters.size(); ++i)
	{
		if (_ocharacters[i] != NULL)
		{
			_ocharacters[i]->update(clock, input);
			if (_ocharacters[i]->isLive(_level->charactersRaw()[i]) == false)
			{
				delete _ocharacters[i];
				_ocharacters[i] = NULL;
			}
		}
	}
}

void Graphics::Split::draw(gdl::Clock clock)
{
	_shader.bind();
	_map->draw(_shader, clock);
	for (size_t i = 0; i < _ocharacters.size(); ++i)
		if (_ocharacters[i] != NULL)
			_ocharacters[i]->draw(_shader, clock);
}