#include "Graphics/Item.hh"

Graphics::Item::Item(const ::Item* item, gdl::Model* model)
	: Object(item->position()), _item(item), _model(model)
{
 	scale(glm::vec3(0.002, 0.002, 0.002));
	translate(glm::vec3(0, 1, 0));

}

Graphics::Item::~Item()
{

}

bool
Graphics::Item::operator==(const ::Item* other) const
{
	return (other == _item);
}

bool
Graphics::Item::initialize()
{
    _model->setCurrentAnim(0);
    return (true);
}

void
Graphics::Item::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void)clock;
	(void)input;
}

void
Graphics::Item::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
	_texture.bind();
	_model->draw(shader, getTransformation(), GL_QUADS);
	(void)clock;
}
