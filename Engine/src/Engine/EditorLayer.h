#pragma once

#include "Engine/Application.h"
#include "Engine/Layer.h"

#include "Engine/Components/OrthographicCameraComponent.h"
#include "Engine/Graphics/window.h"

#include "Engine/Objects//Shapes/Rectangle.h"

#include "Engine/Components/Components.h"

#include "Engine/Objects/Scene.h"
namespace Engine {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		void OnEvent(sf::Event& event) override;
		void OnUpdate(float& ts) override;
		void Render(sf::RenderTarget& rt) override;
		void OnImGuiRender(sf::RenderTarget& rt) override;

		void RenderFrameBuffer(sf::RenderTarget& rt);


	private:
		sf::RenderTexture* m_RenderTexture;
		Scene* m_ActiveScene;

		WindowProps props;
		//OrthographicCameraComponent m_Camera;

		sf::Sprite sprites[4];
		sf::Texture texture1;

		float colors[3] = { 0.0f, 0.0f, 0.0f, };
		sf::Color m_color;

		TransformComponent tc;

		Entity entt;
		Entity entity;
		Entity m_Camera;
		Entity m_SecondCamera;
		Entity* PrimaryCamera;// = m_Camera;

		bool camera1 = false;
	};

}