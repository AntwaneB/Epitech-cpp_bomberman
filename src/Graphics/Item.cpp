#include "Graphics/Item.hh"

Graphics::Item::Item(const ::Item* item, std::vector<gdl::Model*> models, size_t nb)
	: Object(item->position()), _item(item)
{
 	scale(glm::vec3(0.010, 0.010, 0.010));
	translate(glm::vec3(0, 1, 0));
	if (item->type() == ::Item::RANGE_INCREASER)
		_model = models[nb + 1];
	else if (item->type() == ::Item::SPEED_INCREASER)
		_model = models[nb + 2];
	else
		_model = models[nb + 3];
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
