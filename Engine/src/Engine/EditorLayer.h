#pragma once

#include "Engine/Application.h"
#include "Engine/Layer.h"

#include "Engine/Components/OrthographicCameraComponent.h"
#include "Engine/Graphics/window.h"

#include "Engine/Objects//Shapes/Rectangle.h"

#include "Engine/Components/Components.h"

#include "Engine/Objects/Scene.h"

#include "Engine/Objects/SceneHierarchyPanel.h"


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
		Entity* PrimaryCamera;// = m_Camera;

		WindowProps props;

		TransformComponent tc;

		SceneHierarchyPanel m_Panel;

		// TEMP
		Entity entt;
		Entity entity;
		Entity m_Camera;
		Entity m_SecondCamera;

		sf::Sprite sprites[4];
		sf::Texture texture1;
		bool camera1 = false;
		bool m_SceneIsFocused = false;

		float colors[3] = { 0.0f, 0.0f, 0.0f, };
		sf::Color m_color;
	};

}