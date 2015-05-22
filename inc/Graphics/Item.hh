#ifndef GRAPHICS_ITEM_HPP_
# define	GRAPHICS_ITEM_HPP_

#include <iostream>
#include <string>
#include "Model.hh"
#include "Graphics/Object.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Item.hh"

namespace Graphics
{

	class Item : public Object
	{
	public:
		Item(const ::Item*, gdl::Model*);
		virtual ~Item();

		virtual bool  initialize();
		virtual void  update(gdl::Clock const &clock, gdl::Input &input);
		virtual void  draw(gdl::AShader &shader, gdl::Clock const &clock);

		bool	operator==(const ::Item*) const;

	private:
		const ::Item*	_item;
		gdl::Texture	_texture;
		gdl::Model*		_model;
	};

};

#endif
