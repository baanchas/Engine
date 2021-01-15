#include "enpch.h"
#include "Application.h"

namespace Engine {

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
		}
	}

	void Application::OnUpdate()
	{
		ImGui::SFML::Update(*window->m_Window, clock.restart());
		
		if (m_LayerStack.GetSize() != 0)
			m_LayerStack.top()->OnUpdate(m_Timestep);
	}

	void Application::Render()
	{
		window->m_Window->clear();

		if (m_LayerStack.GetSize() != 0)
			m_LayerStack.top()->Render(*window->m_Window);

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