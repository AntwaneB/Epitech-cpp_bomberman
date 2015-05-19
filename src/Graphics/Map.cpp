#include "Graphics/Map.hh"

Graphics::Map::Map()
{

}

Graphics::Map::~Map()
{

}

bool Graphics::Map::initialize(std::vector<Graphics::Object*> * objects, size_t height, size_t width, std::vector<std::vector<Block*> > map)
{
	/*Object *bomb = new Bomb();
	if (bomb->initialize() == false)
		return (false);
	objects->push_back(bomb);*/
	gdl::Texture*	texture = new gdl::Texture;
	if(texture->load("./libgdl/assets/rock.tga") == false)
	{
		std::cout << "false texture" << std::endl;
		return (false);
	}
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			if (map[y][x] && map[y][x]->visible())
			{
				Object *cube = new Cube(Position(x, y, 1), map[y][x], texture);
				cube->initialize();
				objects->push_back(cube);
			}
		}
	}

	Object *ground = new Ground(Position((width - 1) / 2, (height - 1) / 2, 0.4));
	if (ground->initialize() == false)
		return (false);
	objects->push_back(ground);
	_map = map;
	return (true);
}

bool Graphics::Map::update(std::vector<Graphics::Object*> * objects, size_t height, size_t width, std::vector<std::vector<Block*> > map)
{
	int i = 0;
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			i++;
			if (_map[y][x] != map[y][x])
			{
				std::cout << "Delete[" << y << "][" << x << "]: " << i << std::endl;
				auto it = objects->begin() + i;
				delete *it;
				(*objects)[i] = NULL;
				//objects->erase(objects->begin() + i);
				i--;
			}
		}
	}
	_map = map;
	return (true);
}

void Graphics::Map::draw()
{
}