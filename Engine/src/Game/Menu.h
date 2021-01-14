#pragma once

#include "Engine/Layer.h"

namespace Engine {

	class Menu : public Layer
	{
	public:
		Menu();
		~Menu();

		void OnEvent(sf::Event& event) override;
		void OnUpdate(float& ts) override;
		void Render(sf::RenderTarget& rt) override;
	};

}
