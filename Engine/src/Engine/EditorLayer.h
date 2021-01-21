#pragma once

#include "Engine/Application.h"
#include "Engine/Layer.h"

#include "Engine/Components/OrthographicCameraComponent.h"
#include "Engine/Graphics/window.h"

#include "Game/Player.h"

#include "Engine/Objects//Shapes/Rectangle.h"

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

		void RenderToTexure(sf::RenderTarget& rt);


	private:
		sf::RenderTexture* m_RenderTexture;
		Player* m_Player;

		Rectangle rect_1;
		Rectangle rect_2;

		WindowProps props;
		OrthographicCameraComponent m_Camera;

		sf::Sprite sprites[4];
		sf::Texture texture1;

		float colors[3] = { 0.0f, 0.0f, 0.0f, };
		sf::Color m_color;

		ImGuiViewport* m_Viewport;
		ImGuiWindowFlags m_Windowflags;
	};

}