#pragma once

#include "Engine/Application.h"
#include "Engine/Layer.h"

#include "Engine/Components/OrthographicCameraComponent.h"
#include "Engine/Graphics/window.h"

#include "Game/Player.h"

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


		Player* m_Player;
	private:
		sf::RenderTexture* m_RenderTexture;

		WindowProps props;
		OrthographicCameraComponent m_Camera;
		sf::Sprite sprite;

		ImGuiViewport* m_Viewport;
		ImGuiWindowFlags m_Windowflags;
	};

}