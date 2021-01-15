#include "enpch.h"
#include "OrthographicCamera.h"

namespace Engine {

	OrthographicCamera::OrthographicCamera()
	{
	}

	OrthographicCamera::OrthographicCamera(float sizeX, float sizeY)
	{
		m_View.setSize(sizeX, sizeY);
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::Move(float x, float y)
	{
		m_View.move(x, y);
	}

	void OrthographicCamera::Move(sf::Vector2f vec2f)
	{
		m_View.move(vec2f);
	}

	void OrthographicCamera::SetSize(float x, float y)
	{
		m_View.setSize(m_View.getSize().x + x, m_View.getSize().y + y);
	}

	void OrthographicCamera::Zoom(float factor)
	{
		m_View.zoom(factor);
	}

	void OrthographicCamera::Rotate(float angle)
	{
		m_View.rotate(angle);
	}

	void OrthographicCamera::SetCenter(float x, float y)
	{
		m_View.setCenter(x, y);
	}

	void OrthographicCamera::SetCenter(sf::Vector2f vec2f)
	{
		m_View.setCenter(vec2f);
	}

	void OrthographicCamera::GetCenter() const
	{
		m_View.getCenter();
	}


}
