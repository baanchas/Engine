#include "enpch.h"
#include "GameLayer.h"

namespace Engine {

	GameLayer::GameLayer()
	{
		m_Name = "GameLayer";

		ENGINE_INFO("{0} Layer is Pushed!", m_Name);

		m_Player = new Player("resources/sprites/player/player.png");

		m_Player->SetSpriteScale(0.1f, 0.1f);
		m_Player->SetPosition(100.0f, 100.0f);

		
	}

	GameLayer::~GameLayer()
	{
		delete m_Player;
	}

	void GameLayer::OnEvent(sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == Keyboard::B)
			{
				ENGINE_INFO("B pressed from GameLayer!");
			}
		}
	}

	void GameLayer::OnUpdate(float& ts)
	{
		
	}

	void GameLayer::Render(sf::RenderTarget& rt)
	{
		m_Player->Render(rt);
	}

}