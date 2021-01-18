#pragma once

#include "Application.h"
#include "Layer.h"
#include "imgui.h"
#include "imgui-SFML.h"


namespace Engine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate(float& ts) override;
		void OnEvent(sf::Event& event) override;
		void End(sf::RenderTarget& rt);
	private:
		ImGuiViewport* m_Viewport;
		ImGuiWindowFlags m_Windowflags;
	};
}
