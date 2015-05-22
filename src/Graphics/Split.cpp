#include "Graphics/Split.hh"

Graphics::Split::Split(::Level const * level)
	: _level(level), _model(new gdl::Model)
{
	_map = new Map(level->map());
}

Graphics::Split::~Split()
{
	delete _map;

	for (auto it = _characters.begin(); it != _characters.end(); ++it)
		delete *it;
	for (auto it = _bombs.begin(); it != _bombs.end(); ++it)
		delete *it;
}

bool Graphics::Split::initialize(gdl::Model* model, gdl::Model* model2)
{
	_model = model2;
	if (!_shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER)
	|| !_shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER)
	|| !_shader.build())
		return false;

	glm::mat4 projection = glm::perspective(13.0f, 960.0f / 1080.0f, 0.1f, 100.0f);
	glm::mat4 transformation = glm::lookAt(glm::vec3(0, 90, 0), glm::vec3(6, 0, 6), glm::vec3(-180, 1, -180));

	_shader.bind();
	_shader.setUniform("view", transformation);
	_shader.setUniform("projection", projection);

	_map->initialize();

	for (auto it = _level->characters().begin(); it != _level->characters().end(); ++it)
	{
		for (auto iit = it->second.begin(); iit != it->second.end(); ++iit)
		{
			Character* character = new Graphics::Character(*iit, model);
			character->initialize();
			_characters.push_back(character);
		}
	}
	return (true);
}

void Graphics::Split::update(gdl::Clock clock, gdl::Input input)
{
	_map->update();

	auto bombs = _level->bombsRaw();
	if (_bombs.size() != bombs.size())
	{
		for (auto it = bombs.begin(); it != bombs.end(); ++it)
		{
			Bomb* bomb = new Graphics::Bomb(*it, _model);
			bomb->initialize();
			_bombs.push_back(bomb);
		}
	}

	auto items = _level->itemsRaw();
	if (_items.size() != items.size())
	{
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			Item* item = new Graphics::Item(*it, _model);
			item->initialize();
			_items.push_back(item);
		}
	}

	items = _level->itemsRaw();
	for (auto it = _items.begin(); it != _items.end(); ++it)
	{
		bool exists = false;
		for (auto iit = items.begin(); iit != items.end() && !exists; ++iit)
		{
			exists = *it && *(*it) == *iit;
		}
		if (!exists)
		{
			delete (*it);
			it = _items.erase(it);
			--it;
		}
		else
			(*it)->update(clock, input);
	}

	bombs = _level->bombsRaw();
	for (auto it = _bombs.begin(); it != _bombs.end(); ++it)
	{
		bool exists = false;
		for (auto iit = bombs.begin(); iit != bombs.end() && !exists; ++iit)
		{
			exists = *it && *(*it) == *iit;
		}
		if (!exists)
		{
			delete (*it);
			it = _bombs.erase(it);
			--it;
		}
		else
			(*it)->update(clock, input);
	}

	auto characters = _level->charactersRaw();
	for (auto it = _characters.begin(); it != _characters.end(); ++it)
	{
		bool exists = false;
		for (auto iit = characters.begin(); iit != characters.end() && !exists; ++iit)
		{
			exists = *it && *(*it) == *iit;
		}
		if (!exists)
		{
			delete (*it);
			it = _characters.erase(it);
			--it;
		}
		else
			(*it)->update(clock, input);
	}
}

void Graphics::Split::draw(gdl::Clock clock)
{
	_shader.bind();
	_map->draw(_shader, clock);

	for (auto it = _characters.begin(); it != _characters.end(); ++it)
		(*it)->draw(_shader, clock);
	for (auto it = _bombs.begin(); it != _bombs.end(); ++it)
		(*it)->draw(_shader, clock);
	for (auto it = _items.begin(); it != _items.end(); ++it)
		(*it)->draw(_shader, clock);
}