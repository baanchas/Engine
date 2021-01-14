#include "enpch.h"
#include "Player.h"

namespace Engine {

	Player::Player() 
	{
		m_Name = "Player";
	}

	Player::Player(std::string texturePath)
	{
		m_Name = "Player";

		if (m_Texture.loadFromFile(texturePath))
			m_Sprite.setTexture(m_Texture);
		else
			ENGINE_ERROR("{0}: Can not load a texture from this file [{1}], make sure that you pointed the right way!", m_Name, texturePath);
	}

	Player::~Player()
	{
	}

	void Player::Render(sf::RenderTarget& rt)
	{
		rt.draw(this->m_Sprite);
	}
}