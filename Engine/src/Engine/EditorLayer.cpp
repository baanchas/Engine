#include "enpch.h"
#include "EditorLayer.h"
#include "Engine/Application.h"

namespace Engine {

	EditorLayer::EditorLayer()
	{

		m_Name = "Editor Layer";

		ENGINE_INFO("{0} Layer is Pushed!", m_Name);

		m_Windowflags |= ImGuiWindowFlags_MenuBar | ImGuiDockNodeFlags_None | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		m_Player = new Player();

		m_Camera.SetSize(props.Width, props.Height);

		texture1.loadFromFile("resources/sprites/checkerboard.png");
		for (int i = 0; i < 4; i++)
		{
			sprites[i].setTexture(texture1);
			sprites[i].setScale(6, 6);
			if (i % 2)
				sprites[i].setPosition((i / 2) * sprites[i].getTexture()->getSize().x * 6, 0);
			else
				sprites[i].setPosition((i / 2) * sprites[i].getTexture()->getSize().x * 6, 2 * sprites[i].getTexture()->getSize().y * sprites[i].getScale().y / 2);
		}

		rect_1.SetSize(sf::Vector2f(200, 200));
		rect_1.SetPosition(200, 200);
		rect_1.SetCenterOriginFrom(200, 200);
		rect_1.SetColor(sf::Color::Red);
		rect_2.SetSize(sf::Vector2f(300, 300));
		rect_2.SetCenterOriginFrom(200, 200);
		rect_2.SetColor(sf::Color::Cyan);
		rect_2.SetPosition(500, 500);
	}

	EditorLayer::~EditorLayer()
	{
		delete m_Player;
		delete m_Viewport;
		delete m_RenderTexture;
	}

	void EditorLayer::OnEvent(sf::Event& event)
	{
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
		for (auto& sprite : sprites)
		{
			rt.draw(sprite);
		}
		
		rect_1.Render(rt);
		rect_1.Rotate(1);
		rect_2.Render(rt);
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
		ImGui::PopStyleVar(2);

		// DockSpace

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowMinSize.x = 370.0f;
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


		//-------- Render scene to ImGui window


		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Change Color", colors, ImGuiColorEditFlags_InputRGB);
		
		ImGui::End();


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Scene");
		ImGui::PopStyleVar();


		ImVec2 AvailableContentSize = ImGui::GetContentRegionAvail();

		sf::RenderTexture renderTarget;
		renderTarget.create(AvailableContentSize.x, AvailableContentSize.y);
		renderTarget.clear();
		//ENGINE_INFO("{0} {1}", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
		rect_2.SetColor(sf::Color(colors[0] * 255, colors[1] * 255, colors[2] * 255));

		renderTarget.setView(m_Camera.m_View);

		m_Camera.CalculateView(AvailableContentSize.x, AvailableContentSize.y);

		RenderToTexure(renderTarget);
		renderTarget.display();

		ImGui::Image(renderTarget.getTexture(), sf::Vector2f(AvailableContentSize.x, AvailableContentSize.y), sf::FloatRect(0, 0, AvailableContentSize.x, AvailableContentSize.y));

		ImGui::End();

		ImGui::SFML::Render(*Application::Get()->mp_Window->m_Window);

	}
}