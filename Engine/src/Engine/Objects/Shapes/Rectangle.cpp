#include "enpch.h"
#include "Rectangle.h"

namespace Engine {

	Rectangle::Rectangle()
	{
		m_Name = "Rectangle";
	}

	Rectangle::~Rectangle()
	{
	}

	void Rectangle::Render(sf::RenderTarget& rt)
	{
		rt.draw(m_RectangleShape);
	}
	
	void Rectangle::Update(float& ts)
	{
	}

}