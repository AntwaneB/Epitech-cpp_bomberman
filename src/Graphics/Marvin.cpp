#include "Graphics/Marvin.hh"

Graphics::Marvin::Marvin()
{
  scale(glm::vec3(0.0025, 0.0025, 0.0025));
  translate(glm::vec3(0.5, 0, 0.5));
}

Graphics::Marvin::~Marvin()
{

}

bool		Graphics::Marvin::initialize()
{
    if (_model.load("./libgdl/assets/marvin.fbx") == false)
      {
	     std::cout << "Cannot load the marvin model" << std::endl;
	     return (false);
      }
    _model.setCurrentAnim(0);
    return (true);
}

void Graphics::Marvin::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)clock;
	(void)input;
}

void Graphics::Marvin::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model.draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
