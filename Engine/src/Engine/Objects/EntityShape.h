#pragma once

#include "Entity.h"

namespace Engine {

	class EntityShape : public Entity
	{
	public:
		EntityShape();
		virtual ~EntityShape();

		virtual void Render(sf::RenderTarget& rt) override {};
		virtual void Update(float& ts) override {};
	protected:
		std::string m_Name;
	};

}
