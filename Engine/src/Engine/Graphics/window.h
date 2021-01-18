#pragma once

#include "enpch.h"

namespace Engine {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;

		WindowProps(const std::string& title = "VI Games",
			unsigned int width = 1280,
			unsigned int height = 720,
			bool VSync = true)
			: Title(title), Width(width), Height(height), VSync(VSync)
		{
		}
	};

	class Window
	{
	public:
		Window() 
		{
			m_Window = new sf::RenderWindow(sf::VideoMode(props.Width, props.Height), props.Title); 
			SetVSync(props.VSync);
		}
		~Window() { delete this->m_Window; };

		inline sf::RenderWindow* GetWindow() const { return m_Window; }

		inline unsigned int GetWidth() const { return m_Window->getSize().x; }
		inline unsigned int GetHeight() const { return m_Window->getSize().y; }

		void SetVSync(bool& VSync) { m_Window->setVerticalSyncEnabled(VSync); }

	public:
		sf::RenderWindow* m_Window;

	private:
		WindowProps props;
	};

}