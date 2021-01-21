#pragma once

#include "Entity.h"

namespace Engine {

	class EntityDrawable : public Entity
	{
	public:
		EntityDrawable();
		virtual ~EntityDrawable();

		virtual void Update(float& ts) override {};
		virtual void Render(sf::RenderTarget& rt) override;

		virtual void SetPosition(float x, float y) { m_Sprite.setPosition(x, y); }
		virtual void LoadTextureFromFile(std::string path) { m_Texture.loadFromFile(path); }
		virtual void SetTextureToSprite() { m_Sprite.setTexture(m_Texture, true); }
		virtual void SetSpriteScale(float x, float y) { m_Sprite.setScale(x, y); }

		virtual inline sf::FloatRect GetGlobalBounds() const { return m_Sprite.getGlobalBounds(); }
				
		virtual const inline sf::Vector2f& GetPosition() const { return m_Sprite.getPosition(); }

		virtual void Move(float xOffset, float yOffset) { m_Sprite.move(xOffset, yOffset); }
		virtual void Move(sf::Vector2f vec2f) { m_Sprite.move(vec2f); }

		virtual void SetOrigin(float sizeX, float sizeY) { m_Sprite.setOrigin(sizeX / 2, sizeY / 2); }

		virtual void Rotate(float angle) { m_Sprite.rotate(angle); }

	protected:

		std::string m_Name;
		sf::Texture m_Texture;
		sf::Sprite m_Sprite;

	};

}