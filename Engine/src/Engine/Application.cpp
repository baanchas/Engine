#include "enpch.h"
#include "Application.h"


namespace Engine {

	Engine::Application* Engine::Application::s_Instance = new Engine::Application();

	Application::Application()
	{
		mp_Window = new Window();

		ImGui::SFML::Init(*mp_Window->m_Window);
		Log::InitLog();

		PushLayer(new EditorLayer());
	}

	void Application::Run()
	{
		while (mp_Window->m_Window->isOpen())
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
		while (mp_Window->m_Window->pollEvent(event))
		{
			if (m_Event.type == sf::Event::Closed)
				mp_Window->m_Window->close();

			ImGui::SFML::ProcessEvent(event);

			if (m_LayerStack.GetSize() != 0)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnEvent(event);
			}
		}
	}

	void Application::OnUpdate()
	{
		ImGui::SFML::Update(*Application::Get()->mp_Window->m_Window, Application::Get()->GetTime().restart());

		if (m_LayerStack.GetSize() != 0)
		{
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(m_Timestep);
			}
		}

	}

	void Application::Render()
	{
		mp_Window->m_Window->clear();

		if (m_LayerStack.GetSize() != 0)
		{


			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender(*mp_Window->m_Window);
			}
			for (Layer* layer : m_LayerStack)
			{
				layer->Render(*mp_Window->m_Window);
			}

		}
		
		mp_Window->m_Window->display();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_LayerStack.PopOverlay(layer);
	}

}