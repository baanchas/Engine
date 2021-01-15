#pragma once

#include "Engine/Graphics/window.h"
#include "Engine/LayerStack.h"

#include "Game/Menu.h"
#include "Game/GameLayer.h"

#include "Engine/Camera/OrthographicCamera.h"

#include "imgui.h"
#include "imgui-sfml.h"

namespace Engine {

	class Application
	{

	public:
		Application();
		~Application() { delete window; };

		void init();

		void Run();
		void OnEvent(sf::Event& event);
		void OnUpdate();
		void Render();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		static inline sf::RenderWindow* GetWindow() { return window->m_Window; }

		void UpdateTimestep() { m_Timestep = clock.restart().asSeconds(); }
	public:
		static Window* window;

	private:
		sf::Color bgColor;
		LayerStack m_LayerStack;

		float color[3] = { 0.f, 0.f, 0.f };
		float m_Timestep;

		//sf::View _Camera;
		OrthographicCamera m_Camera;

		sf::Event m_Event;
		sf::Clock clock;
	};

	//Application* CreateApplication();
}
