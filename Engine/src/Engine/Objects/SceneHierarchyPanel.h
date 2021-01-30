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

	private:
		Scene* m_Context;
		Entity m_Selected;
		friend class Scene;
	};

}