#include "enpch.h"
#include "Application.h"

namespace Engine {

	Window* Application::window;

	Application::Application()
	{
		init();
		//PushLayer(new Menu());
		PushLayer(new GameLayer());
	}

	void Application::init()
	{
		window = new Window();

		ImGui::SFML::Init(*window->m_Window);
		Log::InitLog();

		m_Camera.m_View.setSize(window->GetWidth(), window->GetHeight());
		window->m_Window->setView(m_Camera.m_View);

	}

	void Application::Run()
	{
		while (window->m_Window->isOpen())
		{
			UpdateTimestep();
			OnEvent(m_Event);
			OnUpdate();
			Render();
		}
		ImGui::SFML::Shutdown();
	}

	void Application::OnEvent(sf::Event& event)
	{
		while (window->m_Window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (m_Event.type == sf::Event::Closed)
				window->m_Window->close();

			if (m_LayerStack.GetSize() != 0)
				m_LayerStack.top()->OnEvent(event);

			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta == 1)
				{
					m_Camera.Zoom(0.95f);
				}
				else if (event.mouseWheel.delta == -1)
				{
					m_Camera.Zoom(1.05f);
				}
			}

		}
	}

	void Application::OnUpdate()
	{
		ImGui::SFML::Update(*window->m_Window, clock.restart());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			m_Camera.Move(-m_Camera.speed, 0.0f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			m_Camera.Move(+m_Camera.speed, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			m_Camera.Move(0.0f, -m_Camera.speed);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			m_Camera.Move(0.0f, +m_Camera.speed);


		if (m_LayerStack.GetSize() != 0)
			m_LayerStack.top()->OnUpdate(m_Timestep);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_Camera.Move(sf::Vector2f(1.0f, 1.0f));
			ENGINE_INFO("Camera center is {0}, {1}", m_Camera.m_View.getCenter().x, m_Camera.m_View.getCenter().y);
		}

	}

	void Application::Render()
	{
		window->m_Window->setView(m_Camera.m_View);

		window->m_Window->clear();

		if (m_LayerStack.GetSize() != 0)
			m_LayerStack.top()->Render(*window->m_Window);

		ImGui::Begin("Sample window");
		ImGui::End();

		ImGui::SFML::Render(*window->m_Window);

		window->m_Window->display();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}


}