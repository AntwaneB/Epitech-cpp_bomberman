#include "Graphics/Map.hh"

Graphics::Map::Map()
{

}

Graphics::Map::~Map()
{

}

bool Graphics::Map::initialize(std::vector<Graphics::Object*> * objects, size_t height, size_t width, std::vector<std::vector<Block*> > map)
{
	Object *ground = new Ground(Position((width - 1) / 2, (height - 1) / 2, 0.4));
	if (ground->initialize() == false)
		return (false);
	objects->push_back(ground);

	Object *bomb = new Bomb();
	if (bomb->initialize() == false)
		return (false);
	objects->push_back(bomb);

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			if (map[y][x] && map[y][x]->visible())
			{
				Object *cube = new Cube(Position(x, y, 1), map[y][x]);
				cube->initialize();
				objects->push_back(cube);
			}
		}
	}
	return (true);
}

bool Graphics::Map::update()
{
	return (true);
}

void Graphics::Map::draw()
{
}