#include "enpch.h"
#include "OrthographicCameraComponent.h"
#include "Engine/Application.h"

namespace Engine {

	OrthographicCameraComponent::OrthographicCameraComponent()
	{
		//m_View.setCenter(640, 360);
	}

	OrthographicCameraComponent::OrthographicCameraComponent(float sizeX, float sizeY)
	{
		m_View.setSize(sizeX, sizeY);
	}

	OrthographicCameraComponent::~OrthographicCameraComponent()
	{
	}

	void OrthographicCameraComponent::OnEvent(sf::Event& event)
	{

		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta == 1)
			{
				ZoomIn();
			}
			else if (event.mouseWheel.delta == -1)
			{
				ZoomOut();
			}

			ENGINE_WARNING("Zoomlevel is {0}", m_zoomLevel);
		}
	}

	void OrthographicCameraComponent::CalculateView(float x, float y)
	{
		m_View.setSize(x, y);

		if (1280.0f / x > 720.0f / y)
		{
			m_View.zoom(m_zoomLevel * (1280.0f / x));
		}
		else
		{
			m_View.zoom(m_zoomLevel * (720.0f / y));
		}
	}


	void OrthographicCameraComponent::CalculateView(sf::Vector2f vec)
	{
		m_View.setSize(vec.x, vec.y);

		if (1280.0f / vec.x > 720.0f / vec.y)
		{
			m_View.zoom(m_zoomLevel * (1280.0f / vec.x));
		}
		else
		{
			m_View.zoom(m_zoomLevel * (720.0f / vec.y));
		}
	}

	void OrthographicCameraComponent::OnUpdate(float& ts)
	{
		// TEMP
		m_oldCenter = m_View.getCenter();
	}


	void OrthographicCameraComponent::SetSize(float x, float y)
	{
		m_View.setSize(x, y);
	}

	void OrthographicCameraComponent::SetCenter(float x, float y)
	{
		m_View.setCenter(x, y);
	}

	void OrthographicCameraComponent::SetCenter(sf::Vector2f vec)
	{
		m_View.setCenter(vec);
	}

	void OrthographicCameraComponent::SetRotation(float r)
	{
		m_View.setRotation(r);
	}

	void OrthographicCameraComponent::ZoomIn()
	{
		m_View.zoom(0.95f);
		m_zoomLevel = m_zoomLevel * 0.95f;
	}

	void OrthographicCameraComponent::ZoomOut()
	{
		m_View.zoom(1.05f);
		m_zoomLevel = m_zoomLevel * 1.05f;
	}
}
