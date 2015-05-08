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
if (!_shader.load("./libgdl/shaders/basic.fp", GL_FRAGMENT_SHADER) 
|| !_shader.load("./libgdl/shaders/basic.vp", GL_VERTEX_SHADER)
|| !_shader.build())
	return false;
glm::mat4 projection;
glm::mat4 transformation;
projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
_shader.bind();
_shader.setUniform("view", transformation);
_shader.setUniform("projection", projection);
for (int y = 0; y <= 15; y++)
{
for (int x = 0; x <= 15; x++)
{	
Object *cube = new Cube(x, y, 0);
if (cube->initialize() == false)
	return (false);
_objects.push_back(cube);
}
}
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