#pragma once

#include "enpch.h"

#include "OrthographicCameraComponent.h"
#include "Engine/Objects/ScriptableEntity.h"


namespace Engine {


	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(std::string tag)
			: Tag(tag) {}

		inline std::string GetTag() const
		{
			return Tag;
		}

		operator std::string& () { return Tag; }
		operator const std::string& () { return Tag; }
	};

	struct TransformComponent
	{
		sf::Vector2f Scale = { 1.0f, 1.0f };
		sf::Vector2f Position = { 0.0f, 0.0f };
		float Rotation = 0.0f;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(sf::Vector2f& position)
			: Position(position) {}

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


		operator sf::Vector2f& () { return Position; }
		operator float () { return Position.x, Position.y; }
		operator const sf::Vector2f& () { return Position; }
	};

	struct ColorComponent
	{
		sf::Color Color = sf::Color(0, 0 ,0);

		ColorComponent() = default;
		ColorComponent(const ColorComponent&) = default;
		ColorComponent(sf::Color color)
			: Color(color) {}

		operator sf::Color& () { return Color; }
		operator const sf::Color& () { return Color; }
	};

	struct RectangleCOmponent
	{
		sf::Vector2f Size = sf::Vector2f(100, 100);

		sf::RectangleShape rect = sf::RectangleShape(Size);


		RectangleCOmponent() = default;
		RectangleCOmponent(const RectangleCOmponent&) = default;
		RectangleCOmponent(sf::RectangleShape& rect)
			: rect(rect) {}
		RectangleCOmponent(sf::Vector2f vec)
			: rect(sf::Vector2f(vec)) {}

		void SetOrigin()
		{
			rect.setOrigin(Size.x / 2, Size.y / 2);
		}

		operator sf::RectangleShape& () { return rect; }
		operator const sf::RectangleShape& () { return rect; }
	};

	struct SpriteComponent
	{
		sf::Texture Texture;
		sf::Sprite Sprite;
		sf::Vector2u Size = Texture.getSize();
		
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(sf::Sprite sprite)
			: Sprite(sprite) {}

		SpriteComponent(std::string path)
		{
			if (Texture.loadFromFile(path))
			{
				Sprite.setTexture(Texture);
			}
			else
			{
				ENGINE_INFO("Can't load texture from this file! Make sure that the path is correct!");
			}
		}

		void SetOrigin()
		{
			Sprite.setOrigin((float)Size.x / 2, (float)Size.y / 2);
		}
	};

	struct CameraComponent
	{
		OrthographicCameraComponent Camera;
		bool primary = false;

		CameraComponent() {};
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		

		ScriptableEntity*(*InstantiateFunction)();
		void (*DestroyInstanceFunction)(NativeScriptComponent*);


		template<typename T>
		void Bind()
		{
			InstantiateFunction = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyInstanceFunction = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}

