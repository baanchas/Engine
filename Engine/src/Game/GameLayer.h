#pragma once

#include "Engine/Layer.h"
#include "Player.h"

namespace Engine {

	class GameLayer : public Layer
	{
	public:
		GameLayer();
		~GameLayer();

		void OnEvent(sf::Event& event) override;
		void OnUpdate(float& ts) override;
		void Render(sf::RenderTarget& rt) override;
		
	private:
		Player* m_Player;
	};

}