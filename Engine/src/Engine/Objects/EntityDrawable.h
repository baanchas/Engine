#pragma once

#include "Entity.h"

namespace Engine {

	class EntityDrawable : public Entity
	{
	public:
		EntityDrawable();
		virtual ~EntityDrawable();

		virtual void Render(sf::RenderTarget& rt) override;

		virtual void SetPosition(float x, float y) { m_Sprite.setPosition(x, y); }
		virtual void LoadTextureFromFile(std::string path) { m_Texture.loadFromFile(path); }
		virtual void SetTextureToSprite() { m_Sprite.setTexture(m_Texture, true); }
		virtual void SetSpriteScale(float x, float y) { m_Sprite.setScale(x, y); }

		inline virtual sf::Vector2f GetPosition() const	{ return m_Sprite.getPosition(); }

		std::string m_Name;
		sf::Texture m_Texture;
		sf::Sprite m_Sprite;
	protected:

	};

}