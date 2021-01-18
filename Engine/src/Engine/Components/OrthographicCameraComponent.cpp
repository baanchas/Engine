#include "enpch.h"
#include "OrthographicCameraComponent.h"
#include "Engine/Application.h"

namespace Engine {

	OrthographicCameraComponent::OrthographicCameraComponent()
	{
		m_View.setCenter(640, 360);
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
		if (event.type == sf::Event::Resized)
		{
			//CalculateView(Application::Get()->mp_Window->GetWidth(), Application::Get()->mp_Window->GetHeight());
			/*if (m_OldWidth != Application::Get()->mp_Window->GetWidth() && m_OldHeight == Application::Get()->mp_Window->GetHeight())
			{
				m_View.setSize(Application::Get()->mp_Window->GetWidth(), Application::Get()->mp_Window->GetHeight());
				m_zoomLevel = m_zoomLevel * (m_OldWidth / Application::Get()->mp_Window->GetWidth());
				m_View.zoom(m_zoomLevel);
				m_OldWidth = Application::Get()->mp_Window->GetWidth();
			}
			else if (m_OldWidth == Application::Get()->mp_Window->GetWidth() && m_OldHeight != Application::Get()->mp_Window->GetHeight())
			{
				m_View.setSize(Application::Get()->mp_Window->GetWidth(), Application::Get()->mp_Window->GetHeight());
				m_zoomLevel = m_zoomLevel * (m_OldHeight / Application::Get()->mp_Window->GetHeight());
				m_View.zoom(m_zoomLevel);
				m_OldHeight = Application::Get()->mp_Window->GetHeight();
			}
			else if (m_OldWidth != Application::Get()->mp_Window->GetWidth() && m_OldHeight != Application::Get()->mp_Window->GetHeight())
			{
				if (m_OldWidth / Application::Get()->mp_Window->GetWidth() > m_OldHeight / Application::Get()->mp_Window->GetHeight())
				{
					m_View.setSize(Application::Get()->mp_Window->GetWidth(), Application::Get()->mp_Window->GetHeight());
					m_zoomLevel = m_zoomLevel * (m_OldWidth / Application::Get()->mp_Window->GetWidth());
					m_View.zoom(m_zoomLevel);

				}
				else
				{
					m_View.setSize(Application::Get()->mp_Window->GetWidth(), Application::Get()->mp_Window->GetHeight());
					m_zoomLevel = m_zoomLevel * (m_OldHeight / Application::Get()->mp_Window->GetHeight());
					m_View.zoom(m_zoomLevel);
					
				}
				m_OldWidth = Application::Get()->mp_Window->GetWidth();
				m_OldHeight = Application::Get()->mp_Window->GetHeight();
			}*/
		}
	
		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta == 1)
			{
				m_View.zoom(0.95f);
				m_zoomLevel = m_zoomLevel * 0.95f;
			}
			else if (event.mouseWheel.delta == -1)
			{
				m_View.zoom(1.05f);
				m_zoomLevel = m_zoomLevel * 1.05f;
			}
		}
	}

	void OrthographicCameraComponent::CalculateView(float x, float y)
	{
		if (m_OldWidth != x && m_OldHeight == y)
		{
			m_View.setSize(x, y);
			m_zoomLevel = m_zoomLevel * (m_OldWidth / x);
			m_View.zoom(m_zoomLevel);
			m_OldWidth = x;
		}
		else if (m_OldWidth == x && m_OldHeight != y)
		{
			m_View.setSize(x, y);
			m_zoomLevel = m_zoomLevel * (m_OldHeight / y);
			m_View.zoom(m_zoomLevel);
			m_OldHeight = y;
		}
		else if (m_OldWidth != x && m_OldHeight != y)
		{
			if (m_OldWidth / x > m_OldHeight / y)
			{
				m_View.setSize(x, y);
				m_zoomLevel = m_zoomLevel * (m_OldWidth / x);
				m_View.zoom(m_zoomLevel);
				m_OldWidth = x;
				m_OldHeight = y;
			}
			else
			{
				m_View.setSize(x, y);
				m_zoomLevel = m_zoomLevel * (m_OldHeight / y);
				m_View.zoom(m_zoomLevel);
				m_OldWidth = x;
				m_OldHeight = y;
			}

		}
	}

	void OrthographicCameraComponent::OnUpdate(float& ts)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			m_View.move(-speed, 0.0f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			m_View.move(+speed, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			m_View.move(0.0f, -speed);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			m_View.move(0.0f, +speed);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Home))
			m_View.rotate(3.0f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::End))
			m_View.rotate(-3.0f);

	 	m_oldCenter = m_View.getCenter();
	}


	void OrthographicCameraComponent::SetSize(float x, float y)
	{
		m_View.setSize(x, y);
	}
}
