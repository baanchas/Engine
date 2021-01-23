#pragma once

#include "enpch.h"

namespace Engine {

	struct Component
	{
		std::string m_Name;
	};

	struct TransformComponent
	{
		sf::Vector2f Scale = { 1.0f, 1.0f };
		sf::Vector2f Position = { 0.0f, 0.0f };
		float Rotation = 0.0f;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(sf::Vector2f& scale)
			: Scale(scale) {}

		inline sf::Vector2f GetTransform() const
		{
			return Scale;
		}

		inline sf::Vector2f GetPosition() const
		{
			return Position;
		}

		inline float GetRotation() const
		{
			return Rotation;
		}


		operator sf::Vector2f& () { return Scale; }
		operator const sf::Vector2f& () { return Scale; }
	};

	struct ColorComponent
	{
		sf::Color Color = sf::Color(0, 0, 0);

		ColorComponent() = default;
		ColorComponent(const ColorComponent&) = default;
		ColorComponent(sf::Color color)
			: Color(color) {}

		operator sf::Color& () { return Color; }
		operator const sf::Color& () { return Color; }
	};

	struct RectangleCOmponent
	{
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(100, 100));

		RectangleCOmponent() = default;
		RectangleCOmponent(const RectangleCOmponent&) = default;
		RectangleCOmponent(sf::RectangleShape& rect)
			: rect(rect) {}


		operator sf::RectangleShape& () { return rect; }
		operator const sf::RectangleShape& () { return rect; }
	};
}

