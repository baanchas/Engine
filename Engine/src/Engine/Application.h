#pragma once

#include "Engine/Graphics/window.h"
#include "Engine/LayerStack.h"

#include "Engine/Components/OrthographicCameraComponent.h"

#include "Layer.h"

#include "Engine/ImGuiLayer.h"
#include "Engine/EditorLayer.h"


namespace Engine {

	class Application
	{

	public:
		
		~Application() { delete mp_Window; };

		void Run();
		void OnEvent(sf::Event& event);
		void OnUpdate();
		void Render();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		void Close() { mp_Window->m_Window->close(); }

		void UpdateTimestep() { m_Timestep = clock.restart().asSeconds(); }

		inline sf::RenderWindow* GetWindow() { return mp_Window->m_Window; }
		inline sf::Clock& GetTime() { return clock; }

		static Application* Get() { return s_Instance; }
	public:
		Window* mp_Window;

	private:
		
		LayerStack m_LayerStack;
		//ImGuiLayer* m_ImGuiLayer;

		float m_Timestep;

		sf::Event m_Event;
		sf::Clock clock;


		static Application* s_Instance;

		Application();
	};

}
