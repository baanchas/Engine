#include "enpch.h"
#include "EditorLayer.h"
#include "Engine/Application.h"

namespace Engine {

	EditorLayer::EditorLayer()
	{

		m_Name = "Editor Layer";

		ENGINE_INFO("{0} Layer is Pushed!", m_Name);

		//m_RenderTexture = new sf::RenderTexture();

		/*if (!m_RenderTexture->create(1280, 720))
		{
			ENGINE_INFO("error to create rendertesture");
		}*/

		m_Windowflags |= ImGuiWindowFlags_MenuBar | ImGuiDockNodeFlags_None | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		m_Player = new Player("resources/sprites/player/player.png");

		m_Player->SetSpriteScale(0.1f, 0.1f);
		m_Player->SetPosition(100.0f, 100.0f);
		
		m_Camera.SetSize(props.Width, props.Height);
	}

	EditorLayer::~EditorLayer()
	{
		delete m_Player;
	}

	void EditorLayer::OnEvent(sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == Keyboard::B)
			{
				ENGINE_INFO("B pressed from Editor Layer!");
			}
		}

		m_Camera.OnEvent(event);
	}

	void EditorLayer::OnUpdate(float& ts)
	{
		m_Camera.OnUpdate(ts);
	}

	void EditorLayer::Render(sf::RenderTarget& rt)
	{

	}

	void EditorLayer::RenderToTexure(sf::RenderTarget& rt)
	{

		m_Player->Render(rt);


	}

	void EditorLayer::OnImGuiRender(sf::RenderTarget& rt)
	{
		
		bool dockspaceOpen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		m_Viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(m_Viewport->Pos);
		ImGui::SetNextWindowSize(m_Viewport->Size);
		ImGui::SetNextWindowViewport(m_Viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, m_Windowflags);
		ImGui::PopStyleVar();

		
		//std::cout << ImGui::GetWindowSize().x;
		ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
	
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Application::Get()->Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();


		ImGui::Begin("esample");

		sf::RenderTexture renderTarget;
		
		renderTarget.create(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

		renderTarget.clear();

		renderTarget.setView(m_Camera.m_View);

		RenderToTexure(renderTarget);

		m_Camera.CalculateView(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

		renderTarget.display();

		ImGui::Image(renderTarget.getTexture(), sf::Vector2f(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y), sf::FloatRect(0, 0, ImGui::GetWindowSize().x,  ImGui::GetWindowSize().y));
			
		ImGui::End();

		ImGui::SFML::Render(*Application::Get()->mp_Window->m_Window);

	}
}