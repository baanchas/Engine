#pragma once

#include "Engine/Objects/EntityDrawable.h"

namespace Engine {

	class Player : public EntityDrawable
	{
	public:
		Player();
		Player(std::string texturePath);
		~Player();

		void Render(sf::RenderTarget& rt) override;
	private:
	};

}
