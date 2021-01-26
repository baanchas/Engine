#include "enpch.h"
#include "EditorLayer.h"
#include "Engine/Application.h"

namespace Engine {

	EditorLayer::EditorLayer()
	{
		ENGINE_INFO("{0} Layer is Pushed!", m_Name);

		m_Name = "Editor Layer";

		m_ActiveScene = new Scene();
		
		entt = m_ActiveScene->CreateEntity();
		entity = m_ActiveScene->CreateEntity();
		m_Camera = m_ActiveScene->CreateEntity();
		m_SecondCamera = m_ActiveScene->CreateEntity();

		PrimaryCamera = &m_Camera;

		m_Camera.AddComponent<CameraComponent>();
		
		m_SecondCamera.AddComponent<CameraComponent>();
		
		
		entity.AddComponent<RectangleCOmponent>(sf::Vector2f(100, 100));
		auto& rc1 = entity.GetComponent<RectangleCOmponent>();
		rc1.SetOrigin();
		auto& tc1 = entity.GetComponent<TransformComponent>();
		tc1.Position = sf::Vector2f(1000, 200);

		entt.AddComponent<RectangleCOmponent>(sf::Vector2f(200, 200));
		auto& rc = entt.GetComponent<RectangleCOmponent>();
		rc.SetOrigin();
		auto& tc = entt.GetComponent<TransformComponent>();
		tc.Position = sf::Vector2f(400, 400);
		entt.AddComponent<ColorComponent>();

		texture1.loadFromFile("resources/sprites/checkerboard.png");
		for (int i = 0; i < 4; i++)
		{
			sprites[i].setTexture(texture1);
			sprites[i].setScale(6, 6);
			if (i % 2)
				sprites[i].setPosition((i / 2) * (float)sprites[i].getTexture()->getSize().x * 6, 0);
			else
				sprites[i].setPosition((i / 2) * (float)sprites[i].getTexture()->getSize().x * 6, 2 * sprites[i].getTexture()->getSize().y * sprites[i].getScale().y / 2);
		}

		ENGINE_INFO("{0} entities in ActiveScene", m_ActiveScene->Count());
	}

	EditorLayer::~EditorLayer()
	{
		delete m_RenderTexture;
		delete m_ActiveScene;
		delete PrimaryCamera;
	}

	void EditorLayer::OnEvent(sf::Event& event)
	{
		if (PrimaryCamera->HasComponent<CameraComponent>())
		{
			auto& camera = PrimaryCamera->GetComponent<CameraComponent>();
			camera.Camera.OnEvent(event);
		}
	}

	void EditorLayer::OnUpdate(float& ts)
	{
		if (camera1)
		{
			PrimaryCamera = &m_SecondCamera;
		}
		else
		{
			PrimaryCamera = &m_Camera;
		}

		m_ActiveScene->OnUpdate(ts);


		if (PrimaryCamera->HasComponent<CameraComponent>())
		{
			auto& camera = PrimaryCamera->GetComponent<CameraComponent>();
			camera.Camera.OnUpdate(ts);
		}


		auto& cc = entt.GetComponent<ColorComponent>();
		cc.Color = sf::Color((sf::Uint8)(colors[0] * 255), (sf::Uint8)(colors[1] * 255), (sf::Uint8)(colors[2] * 255));

		auto& rc = entt.GetComponent<RectangleCOmponent>();
		rc.rect.rotate(40 * ts);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			auto& tc =entt.GetComponent<TransformComponent>();
			tc.Position += sf::Vector2f(100, 0) * -ts;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			auto& tc = entt.GetComponent<TransformComponent>();
			tc.Position += sf::Vector2f(100, 0) * ts;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			auto& tc = entt.GetComponent<TransformComponent>();
			tc.Position += sf::Vector2f(0, 100) * -ts;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			auto& tc = entt.GetComponent<TransformComponent>();
			tc.Position += sf::Vector2f(0, 100) * ts;
		}

	}

	void EditorLayer::Render(sf::RenderTarget& rt)
	{
		
	}

	void EditorLayer::RenderFrameBuffer(sf::RenderTarget& rt)
	{
		for (auto& sprite : sprites)
		{
			rt.draw(sprite);
		}

		m_ActiveScene->Render(rt);
	}

	void EditorLayer::OnImGuiRender(sf::RenderTarget& rt)
	{
		bool dockspaceOpen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags Windowflags = ImGuiWindowFlags_MenuBar | ImGuiDockNodeFlags_None | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGuiViewport* Viewport = ImGui::GetMainViewport();


		ImGui::SetNextWindowPos(Viewport->Pos);
		ImGui::SetNextWindowSize(Viewport->Size);
		ImGui::SetNextWindowViewport(Viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, Windowflags);
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
		if (ImGui::Checkbox("Camera 2", &camera1));

		ImGui::End();


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Scene");
		ImGui::PopStyleVar();


		ImVec2 AvailableContentSize = ImGui::GetContentRegionAvail();

		sf::RenderTexture renderTarget;
		renderTarget.create((unsigned int)AvailableContentSize.x, (unsigned int)AvailableContentSize.y);
		renderTarget.clear();

		if (PrimaryCamera->HasComponent<CameraComponent>())
		{
			auto& camera = PrimaryCamera->GetComponent<CameraComponent>();
			renderTarget.setView(camera.Camera.m_View);

			camera.Camera.CalculateView(AvailableContentSize.x, AvailableContentSize.y);
		}

		RenderFrameBuffer(renderTarget);
		renderTarget.display();

		ImGui::Image(renderTarget.getTexture(), sf::Vector2f(AvailableContentSize.x, AvailableContentSize.y), sf::FloatRect(0, 0, AvailableContentSize.x, AvailableContentSize.y));

		ImGui::End();

		ImGui::SFML::Render(*Application::Get()->mp_Window->m_Window);

	}
}