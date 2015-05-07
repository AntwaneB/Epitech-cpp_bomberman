#include "Graphics/Cube.hh"

Graphics::Cube::Cube()
{

}

Graphics::Cube::~Cube()
{

}

bool Graphics::Cube::initialize()
{
_speed = 10.0f;
// On charge la texture qui sera affichee sur chaque face du cube
_texture.load("./assets/texture.tga");
// on set la color d'une premiere face
_geometry.setColor(glm::vec4(1, 0, 0, 1));
// tout les pushVertex qui suivent seront de cette couleur
// On y push les vertices d une premiere face
_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
// Les UVs d'une premiere face
_geometry.pushUv(glm::vec2(0.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 1.0f));
_geometry.pushUv(glm::vec2(0.0f, 1.0f));
// ETC ETC
_geometry.setColor(glm::vec4(1, 1, 0, 1));
_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
_geometry.pushUv(glm::vec2(0.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 1.0f));
_geometry.pushUv(glm::vec2(0.0f, 1.0f));
_geometry.setColor(glm::vec4(0, 1, 1, 1));
_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
_geometry.pushUv(glm::vec2(0.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 1.0f));
_geometry.pushUv(glm::vec2(0.0f, 1.0f));
_geometry.setColor(glm::vec4(1, 0, 1, 1));
_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
_geometry.pushUv(glm::vec2(0.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 1.0f));
_geometry.pushUv(glm::vec2(0.0f, 1.0f));
_geometry.setColor(glm::vec4(0, 1, 0, 1));
_geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
_geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
_geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
_geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
_geometry.pushUv(glm::vec2(0.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 1.0f));
_geometry.pushUv(glm::vec2(0.0f, 1.0f));
_geometry.setColor(glm::vec4(0, 0, 1, 1));
_geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
_geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
_geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
_geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
_geometry.pushUv(glm::vec2(0.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 0.0f));
_geometry.pushUv(glm::vec2(1.0f, 1.0f));
_geometry.pushUv(glm::vec2(0.0f, 1.0f));
_geometry.build();
return (true);
}

void Graphics::Cube::update(gdl::Clock const &clock, gdl::Input &input)
{

if (input.getKey(SDLK_UP))
translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
if (input.getKey(SDLK_DOWN))
translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
if (input.getKey(SDLK_LEFT))
translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
if (input.getKey(SDLK_RIGHT))
translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void Graphics::Cube::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
(void)clock;
// On bind la texture pour dire que l'on veux l'utiliser
_texture.bind();
// Et on dessine notre cube
_geometry.draw(shader, getTransformation(), GL_QUADS);
}