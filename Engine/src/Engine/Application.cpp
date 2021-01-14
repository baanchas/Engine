#include "enpch.h"
#include "Application.h"

namespace Engine {

	Application::Application()
	{
		init();
		PushLayer(new Menu());
		PushLayer(new GameLayer());
	}

	void Application::init()
	{
		window = new Window();
		Log::InitLog();
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
	}

	void Application::OnEvent(sf::Event& event)
	{
		while (window->m_Window->pollEvent(event))
		{
			if (m_Event.type == sf::Event::Closed)
				window->m_Window->close();

			m_LayerStack.top()->OnEvent(event);
		}
	}

	void Application::OnUpdate()
	{
		m_LayerStack.top()->OnUpdate(m_Timestep);
	}

	void Application::Render()
	{
		window->m_Window->clear();
		m_LayerStack.top()->Render(*window->m_Window);
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