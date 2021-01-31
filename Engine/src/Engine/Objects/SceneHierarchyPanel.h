#pragma once
#include "Engine/Components/Components.h"
#include "Scene.h"
#include "Entity.h"
#include "imgui.h"


namespace Engine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Scene* context);
		~SceneHierarchyPanel();

		void SetContext(Scene* context);

		void OnImGuiRender();

		void DrawComponents(Entity& entity);

	private:
		float colorBuffer[3];

		Scene* m_Context;
		Entity m_SelectedEntity;
		friend class Scene;
	};

}