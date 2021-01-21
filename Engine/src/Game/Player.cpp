#include "enpch.h"
#include "Player.h"

namespace Engine {

	Player::Player() 
	{
		m_Name = "Player";
		m_Texture.loadFromFile("resources/sprites/player/pizza2.png");
		SetSpriteScale(0.2f, 0.2f);
		m_Sprite.setTexture(m_Texture);
		SetPosition(200.0f, 200.0f);
	}

	Player::Player(std::string texturePath)
	{
		m_Name = "Player";

		if (m_Texture.loadFromFile(texturePath))
			m_Sprite.setTexture(m_Texture);
		else
			ENGINE_ERROR("{0}: Can not load a texture from this file [{1}], make sure that you pointed the right way!", m_Name, texturePath);

		SetSpriteScale(0.1f, 0.1f);
	}

	Player::~Player()
	{

	}

	void Player::Render(sf::RenderTarget& rt)
	{
		//m_Sprite.setOrigin(m_Texture.getSize().x / 2, m_Texture.getSize().y / 2);
		//m_Sprite.rotate(3);
		rt.draw(this->m_Sprite);
	}
}