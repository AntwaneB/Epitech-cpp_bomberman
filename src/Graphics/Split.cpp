#include "Graphics/Split.hh"

Graphics::Split::Split(::Level const * level, int id, size_t splitsCount, size_t size)
	: _level(level), _player(NULL), _size(size), _x(0), _y(0), _splitsCount(splitsCount)
{
	_map = new Map(level->map());
	if (_level->players().size() > 0)
	{
		if (id == 0)
			_player = _level->players().front();
		else
			_player = _level->players().back();
	}
}

Graphics::Split::~Split()
{
	delete _map;

	for (auto it = _characters.begin(); it != _characters.end(); ++it)
		delete *it;
	for (auto it = _bombs.begin(); it != _bombs.end(); ++it)
		delete *it;
}

bool Graphics::Split::initialize(std::vector<gdl::Model*> models)
{
	_models = models;
	if (!_shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER)
	|| !_shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER)
	|| !_shader.build())
		return false;

	glm::mat4 projection = glm::perspective(13.0f, (1920.0f / _splitsCount) / 1080.0f, 0.1f, 150.0f);

	_shader.bind();
	moveCamera();
	_shader.setUniform("projection", projection);
	_shader.setUniform("color", glm::vec4(1, 1, 1, 1));
	_map->initialize();

	size_t i = 0;
	for (auto it = _level->characters().begin(); it != _level->characters().end(); ++it, ++i)
	{
		for (auto iit = it->second.begin(); iit != it->second.end(); ++iit)
		{
			Character* character = new Graphics::Character(*iit, _models[i]);
			character->initialize();
			_characters.push_back(character);
		}
	}

	gdl::Texture* texture = new gdl::Texture;
	if (texture->load("./assets/textures/fire.tga") == false)
		std::cout << "Error: fire texture not found." << std::endl;
	_texture = texture;
	return (true);
}

void Graphics::Split::update(gdl::Clock clock, gdl::Input input)
{
	_map->update();
	// Creating new bombs
	auto bombs = _level->bombsRaw();
	for (auto it = bombs.begin(); it != bombs.end(); ++it)
	{
		bool found = false;
		for (auto iit = _bombs.begin(); iit != _bombs.end() && !found; ++iit)
			found = (*(*iit) == (*it));

		if (!found)
		{
			Bomb* bomb = new Graphics::Bomb(*it, _models[_size]);
			bomb->initialize();
			_bombs.push_back(bomb);
		}
	}

	//Creating explosion
	auto explosions = _level->explosions();
	for (auto it = explosions.begin(); it != explosions.end(); ++it)
	{
		bool exist = false;
		for (auto itt = _explosions.begin(); itt != _explosions.end(); ++itt)
			{
				if ((*it).id == (*itt).first)
					exist = true;
			}
		if (exist == false)
		{
			size_t id = (*it).id;
			std::list<Graphics::Object*> explosions2;
			for (auto itt = (*it).positions.begin(); itt != (*it).positions.end(); ++itt)
			{
				//std::cout << v.x() << " " << ((*it).second)[1].y() << std::endl;
				Object *explosion = new Explosion((*itt), _texture);
				explosion->initialize();
				explosions2.push_back(explosion);
			}
			std::pair<size_t, std::list<Graphics::Object*> > paire (id, explosions2);
			_explosions.push_back(paire);
		}
	}

	// Creating new items
	auto items = _level->itemsRaw();
	for (auto it = items.begin(); it != items.end(); ++it)
	{
		bool found = false;
		for (auto iit = _items.begin(); iit != _items.end() && !found; ++iit)
			found = (*(*iit) == (*it));

		if (!found)
		{
			Item* item = new Graphics::Item(*it, _models, _size);
			item->initialize();
			_items.push_back(item);
		}
	}

	// Updating bombs
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

	//Updating explosion
	for (auto it = _explosions.begin(); it != _explosions.end(); ++it)
	{
		auto explosions = _level->explosions();
		bool exist = false;
		for (auto itt = explosions.begin(); itt != explosions.end(); ++itt)
			{
				if ((*it).first == (*itt).id)
					exist = true;
			}
		if (exist == false)
		{
			for (auto itt = (*it).second.begin(); itt != (*it).second.end(); ++itt)
				delete (*itt);
			it = _explosions.erase(it);
			--it;
		}
	}

	// Updating items
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

	// Updating characters
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

	if (input.getKey(SDLK_KP_PLUS) && _height > 30)
		_height -= 2;
	if (input.getKey(SDLK_KP_MINUS) && _height < 150)
		_height += 2;
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
	for (auto it = _explosions.begin(); it != _explosions.end(); ++it)
		for (auto itt = (*it).second.begin(); itt != (*it).second.end(); ++itt)
			(*itt)->draw(_shader, clock);
}

void Graphics::Split::moveCamera()
{
	if (_player)
	{
		_x = _player->position().x();
		_y = _player->position().y();
	}
	else
	{
		_x = _level->map().width() / 2;
		_y = _level->map().height() / 2;
	}
	glm::mat4 transformation = glm::lookAt(glm::vec3(_x, _height, _y), glm::vec3(_x, 0, _y), glm::vec3(0, 1, -180));
	_shader.setUniform("view", transformation);
}
