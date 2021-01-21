#pragma once

#include "Engine/Objects/EntityShape.h"

namespace Engine {

	class Rectangle : public EntityShape
	{
	public:
		Rectangle();
		~Rectangle();

		virtual void Render(sf::RenderTarget& rt) override;
		virtual void Update(float& ts) override;

		
		void SetSize(sf::Vector2f vec) { m_RectangleShape.setSize(vec); }
		inline const sf::Vector2f& GetSize() const { return m_RectangleShape.getSize(); }

		inline sf::FloatRect GetGlobalBounds() const { return m_RectangleShape.getGlobalBounds(); }

		void SetPosition(float x, float y) { m_RectangleShape.setPosition(x, y); }
		const inline sf::Vector2f& GetPosition() const { return m_RectangleShape.getPosition(); }

		void Move(float xOffset, float yOffset) { m_RectangleShape.move(xOffset, yOffset); }
		void Move(sf::Vector2f vec2f) { m_RectangleShape.move(vec2f); }

		void SetOrigin(float x, float y) { m_RectangleShape.setOrigin(x, y); }
		void SetCenterOriginFrom(float sizeX, float sizeY) { m_RectangleShape.setOrigin(sizeX / 2, sizeY / 2); }

		void Rotate(float angle) { m_RectangleShape.rotate(angle); }

		void SetColor(sf::Color color) { m_RectangleShape.setFillColor(color); }
		inline const sf::Color& GetColor() const { return m_RectangleShape.getFillColor(); }
		

	private:
		sf::RectangleShape m_RectangleShape;
	};


}
