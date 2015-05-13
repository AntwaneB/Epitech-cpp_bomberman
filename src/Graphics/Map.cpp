#include "Graphics/Map.hh"

Graphics::Map::Map()
{

}

Graphics::Map::~Map()
{

}

bool Graphics::Map::initialize(std::vector<Graphics::Object*> * objects, unsigned int height, unsigned int width, std::vector<std::vector<int> > map)
{
	Object *ground = new Ground((width - 1) / 2, (height - 1) / 2, 0.4, 0);
	if (ground->initialize() == false)
		return (false);
	objects->push_back(ground);

	Object *marvin = new Marvin();
	if (marvin->initialize() == false)
		return (false);
	objects->push_back(marvin);

	Object *bomb = new Bomb();
	if (bomb->initialize() == false)
		return (false);
	objects->push_back(bomb);

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			if (map[y][x] == 1)
			{
				Object *cube = new Cube(x, y, 1, 1);
				if (cube->initialize() == false)
					return (false);
				objects->push_back(cube);
			}
			else if (map[y][x] == 2)
			{
				Object *cube = new Cube(x, y, 1, 2);
				if (cube->initialize() == false)
					return (false);
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