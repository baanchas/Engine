#include "enpch.h"
#include "EditorLayer.h"
#include "Engine/Application.h"
#include <functional>

namespace Engine {

	EditorLayer::EditorLayer()
	{
		ENGINE_INFO("{0} Layer is Pushed!", m_Name);

		m_Name = "Editor Layer";

		m_ActiveScene = new Scene();
		
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

		// TEMP
		entt = m_ActiveScene->CreateEntity("Cube 1");
		entity = m_ActiveScene->CreateEntity("Cube 2");
		m_Camera = m_ActiveScene->CreateEntity("Camera 1");
		m_SecondCamera = m_ActiveScene->CreateEntity("Camera 2");


		m_Camera->AddComponent<CameraComponent>();

		m_SecondCamera->AddComponent<CameraComponent>();
		
		PrimaryCamera = m_Camera;
		
		// Setup enttities
		entity->AddComponent<RectangleCOmponent>(sf::Vector2f(100, 100));
		auto& rc1 = entity->GetComponent<RectangleCOmponent>();
		rc1.SetOrigin();
		auto& tc1 = entity->GetComponent<TransformComponent>();
		tc1.Position = sf::Vector2f(1000, 200);
		entity->AddComponent<ColorComponent>();

		entt->AddComponent<RectangleCOmponent>(sf::Vector2f(200, 200));
		auto& rc = entt->GetComponent<RectangleCOmponent>();
		rc.SetOrigin();
		auto& tc = entt->GetComponent<TransformComponent>();
		tc.Position = sf::Vector2f(400, 400);
		entt->AddComponent<ColorComponent>();

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


		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
			
			}

			void OnDestroy()
			{
			}

			void OnUpdate(float ts)
			{
				auto& cctc = GetComponent<TransformComponent>();
				if (Input::IsKeyPressed(KeyCodes::Keyboard::Left))
					cctc.Position += sf::Vector2f(-10.f, 0.0f);
				else if (Input::IsKeyPressed(KeyCodes::Keyboard::Right))
					cctc.Position += sf::Vector2f(10.f, 0.0f);

				if (Input::IsKeyPressed(KeyCodes::Keyboard::Up))
					cctc.Position += sf::Vector2f(0.f, -10.0f);
				else if (Input::IsKeyPressed(KeyCodes::Keyboard::Down))
					cctc.Position += sf::Vector2f(0.f, +10.0f);

				if (Input::IsKeyPressed(KeyCodes::Keyboard::Home))
					cctc.Rotation += 3.0f;
				else if (Input::IsKeyPressed(KeyCodes::Keyboard::End))
					cctc.Rotation -= 3.0f;
			}
		};

		m_Panel.SetContext(m_ActiveScene);
	}

	EditorLayer::~EditorLayer()
	{
		delete m_RenderTexture;
		delete m_ActiveScene;
		delete PrimaryCamera;
	}

	void EditorLayer::OnEvent(sf::Event& event)
	{
		if (PrimaryCamera->Valid())
		{
			if (PrimaryCamera->HasComponent<CameraComponent>() && m_SceneIsFocused)
			{
				auto& cc = PrimaryCamera->GetComponent<CameraComponent>();
				cc.Camera.OnEvent(event);
			}
		}
	}

	void EditorLayer::OnUpdate(float& ts)
	{
		if (!PrimaryCamera->Valid())
		{
			for (auto entity : m_ActiveScene->m_Entities)
			{
				if (entity->Valid())
				{
					if (entity->HasComponent<CameraComponent>())
					{
						PrimaryCamera = entity;
					}
				}
			}
		}

		if (camera1)
		{
			if (m_SecondCamera->Valid())
				PrimaryCamera = m_SecondCamera;
		}
		else
		{
			if (m_Camera->Valid())
				PrimaryCamera = m_Camera;
		}
		
		// Updating Scene stuff only when cnene window is active
		if (m_SceneIsFocused)
		{
			m_ActiveScene->OnScenePLay(ts);
		}
		
		m_ActiveScene->OnUpdate(ts);

		if (PrimaryCamera->Valid())
		{
			if (PrimaryCamera->HasComponent<CameraComponent>())
			{
				auto& camera = PrimaryCamera->GetComponent<CameraComponent>();
				camera.Camera.OnUpdate(ts);
			}
		}

		if (entt->Valid())
		{
			auto& rc = entt->GetComponent<TransformComponent>();
			rc.Rotation += 40 * ts;
		}
		//rc.rect.setRotation(40 * ts);

		if (m_SceneIsFocused && entt->Valid())
		{
			if (entt->HasComponent<TransformComponent>())
			{
				auto& tc = entt->GetComponent<TransformComponent>();
				if (Input::IsKeyPressed(KeyCodes::Keyboard::A))
				{
					tc.Position += sf::Vector2f(100, 0) * -ts;
				}
				else if (Input::IsKeyPressed(KeyCodes::Keyboard::D))
				{
					tc.Position += sf::Vector2f(100, 0) * ts;
				}

				if (Input::IsKeyPressed(KeyCodes::Keyboard::W))
				{
					tc.Position += sf::Vector2f(0, 100) * -ts;
				}
				else if (Input::IsKeyPressed(KeyCodes::Keyboard::S))
				{
					tc.Position += sf::Vector2f(0, 100) * ts;
				}
			}
		}


		if (m_SceneIsFocused && PrimaryCamera->Valid())
		{
			auto& cctc = PrimaryCamera->GetComponent<TransformComponent>();
			if (Input::IsKeyPressed(KeyCodes::Keyboard::Left))
				cctc.Position += sf::Vector2f(-10.f, 0.0f);
			else if (Input::IsKeyPressed(KeyCodes::Keyboard::Right))
				cctc.Position += sf::Vector2f(10.f, 0.0f);

			if (Input::IsKeyPressed(KeyCodes::Keyboard::Up))
				cctc.Position += sf::Vector2f(0.f, -10.0f);
			else if (Input::IsKeyPressed(KeyCodes::Keyboard::Down))
				cctc.Position += sf::Vector2f(0.f, +10.0f);

			if (Input::IsKeyPressed(KeyCodes::Keyboard::Home))
				cctc.Rotation += 3.0f;
			else if (Input::IsKeyPressed(KeyCodes::Keyboard::End))
				cctc.Rotation -= 3.0f;
		}
	}

	void EditorLayer::Render(sf::RenderTarget& rt)
	{
		
	}

	void EditorLayer::RenderFrameBuffer(sf::RenderTarget& rt)
	{
		// draw wallpaper
		for (auto& sprite : sprites)
		{
			rt.draw(sprite);
		}

		// Rendering Scene entities
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

		// DockSpace
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, Windowflags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);


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
		//ImGui::setnexwindo

		ImGui::Checkbox("Camera 2", &camera1);

		ImGui::End();


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Scene");
		ImGui::PopStyleVar();

		// Check if scene is foucesd
		if (ImGui::IsWindowFocused() || ImGui::IsWindowHovered())
			m_SceneIsFocused = true;
		else
			m_SceneIsFocused = false;

		ImVec2 AvailableContentSize = ImGui::GetContentRegionAvail();
		// Setting frame buffer
		sf::RenderTexture renderTarget;
		renderTarget.create((unsigned int)AvailableContentSize.x, (unsigned int)AvailableContentSize.y);
		renderTarget.clear();

		// Calculate Camera view
		if (PrimaryCamera->Valid())
		{
			if (PrimaryCamera->HasComponent<CameraComponent>())
			{
				auto& camera = PrimaryCamera->GetComponent<CameraComponent>();
				renderTarget.setView(camera.Camera.m_View);
				camera.Camera.CalculateView(AvailableContentSize.x, AvailableContentSize.y);
				RenderFrameBuffer(renderTarget);
			}
		}
		renderTarget.display();

		ImGui::Image(renderTarget.getTexture(), sf::Vector2f(AvailableContentSize.x, AvailableContentSize.y), sf::FloatRect(0, 0, AvailableContentSize.x, AvailableContentSize.y));

		ImGui::End();

		// Draw Hierarchy Panel
		m_Panel.OnImGuiRender();

		ImGui::SFML::Render(*Application::Get()->mp_Window->m_Window);

	}
}