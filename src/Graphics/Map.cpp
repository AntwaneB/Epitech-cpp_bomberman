#include "Graphics/Map.hh"

Graphics::Map::Map(const ::Map& map)
	: _map(&map)
{

}

Graphics::Map::~Map()
{
	for (unsigned int y = 0; y < _map->height(); y++)
		for (unsigned int x = 0; x < _map->width(); x++)
			delete _blocks[y][x];
}

bool Graphics::Map::initialize()
{
	/*Object *bomb = new Bomb();
	if (bomb->initialize() == false)
		return (false);
	objects->push_back(bomb);*/
	gdl::Texture*	t_rock = new gdl::Texture;
	if (t_rock->load("./libgdl/assets/rock.tga") == false)
	{
		std::cout << "false texture" << std::endl;
		return (false);
	}
	gdl::Texture*	t_wood = new gdl::Texture;
	if (t_wood->load("./libgdl/assets/wood.tga") == false)
	{
		std::cout << "false texture" << std::endl;
		return (false);
	}
	for (unsigned int y = 0; y < _map->height(); y++)
	{
		std::vector<Graphics::Object*> line;
		for (unsigned int x = 0; x < _map->width(); x++)
		{
			if (_map->map()[y][x] && _map->map()[y][x]->visible())
			{
				if (_map->map()[y][x]->texture() == "./libgdl/assets/rock.tga")
				{
					Object *cube = new Cube(Position(x, y, 1), _map->map()[y][x], t_rock);
					cube->initialize();
					line.push_back(cube);
				}
				else if (_map->map()[y][x]->texture() == "./libgdl/assets/wood.tga")
				{
					Object *cube = new Cube(Position(x, y, 1), _map->map()[y][x], t_wood);
					cube->initialize();
					line.push_back(cube);
				}
			}
			else if (!_map->map()[y][x]->visible())
			{
				Object *cube = new Cube(Position(x, y, 1), _map->map()[y][x], t_wood);
				cube->initialize();
				line.push_back(cube);
			}

		}
		_blocks.push_back(line);
	}

	_ground = new Ground(Position((_map->width() - 1) / 2, (_map->height() - 1) / 2, 0.4));
	if (_ground->initialize() == false)
		return (false);
	return (true);
}

bool Graphics::Map::update()
{
	for (unsigned int y = 0; y < _map->height(); y++)
		for (unsigned int x = 0; x < _map->width(); x++)
			if (!_map->map()[y][x]->visible() && _blocks[y][x] != NULL)
				_blocks[y][x] = NULL;
	return (true);
}

void Graphics::Map::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_ground->draw(shader, clock);
	for (unsigned int y = 0; y < _blocks.size(); y++)
		for (unsigned int x = 0; x < _blocks[y].size(); x++)
			if (_blocks[y][x])
				_blocks[y][x]->draw(shader, clock);	
}