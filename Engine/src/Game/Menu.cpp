#include "enpch.h"
#include "Menu.h"

namespace Engine {

	Menu::Menu()
	{
		m_Name = "Menu";

		ENGINE_INFO("Menu Layer is Pushed!");
	}

	Menu::~Menu()
	{
		ENGINE_INFO("Menu Layer is Popped!");
	}

	void Menu::OnEvent(sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == Keyboard::B)
				ENGINE_INFO("B pressed from MenuLayer!");
		}
	}

	void Menu::OnUpdate(float& ts)
	{
	}

	void Menu::Render(sf::RenderTarget& rt)
	{
	}
}