#include "enpch.h"
#include "ImGuiLayer.h"

namespace Engine {

	ImGuiLayer::ImGuiLayer()
	{

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ENGINE_INFO("Imgui layer is pushed!");
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGui::SFML::Shutdown();
	}

	void ImGuiLayer::OnUpdate(float& ts)
	{
		ImGui::SFML::Update(*Application::Get()->mp_Window->m_Window, Application::Get()->GetTime().restart());
	}

	void ImGuiLayer::OnEvent(sf::Event& event)
	{
		ImGui::SFML::ProcessEvent(event);
	}

	void ImGuiLayer::End(sf::RenderTarget& rt)
	{
		ImGui::SFML::Render(rt);
	}
}