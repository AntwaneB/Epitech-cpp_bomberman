#include "Graphics/Map.hh"

Graphics::Map::Map()
{

}

Graphics::Map::~Map()
{
for (size_t i = 0; i < _objects.size(); ++i)
	delete _objects[i];
}

bool Graphics::Map::initialize()
{
if (!_context.start(800, 600, "My bomberman!"))
	return false;
glEnable(GL_DEPTH_TEST);
if (!_shader.load("./LibBomberman_linux_x64/Shaders/basic.fp", GL_FRAGMENT_SHADER) || !_shader.load("./LibBomberman_linux_x64/Shaders/basic.vp", GL_VERTEX_SHADER) // le vertex
|| !_shader.build())
	return false;
glm::mat4 projection;
glm::mat4 transformation;
_shader.bind();
_shader.setUniform("view", transformation);
_shader.setUniform("projection", projection);
Object *cube = new Cube();
if (cube->initialize() == false)
	return (false);
_objects.push_back(cube);
return true;
}

bool Graphics::Map::update()
{
if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
	return false;
// Mise a jour des inputs et de l'horloge de jeu
_context.updateClock(_clock);
_context.updateInputs(_input);
// Mise a jour des differents objets
for (size_t i = 0; i < _objects.size(); ++i)
_objects[i]->update(_clock, _input);
return true;
}

void Graphics::Map::draw()
{
// On clear l'ecran
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// pour utiliser un shader (pour que ce soit ce dernier qui dessine la geometrie) il faut le
// Un seul shader peut etre actif en meme temps
_shader.bind();
// On dessine tous les objets composant la scene
for (size_t i = 0; i < _objects.size(); ++i)
_objects[i]->draw(_shader, _clock);
// On met ensuite a jour l'ecran pour que ce que l'on a dessine s'affiche
_context.flush();
}