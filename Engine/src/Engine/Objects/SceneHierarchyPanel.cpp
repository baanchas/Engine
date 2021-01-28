#include "enpch.h"
#include "SceneHierarchyPanel.h"

namespace Engine {

	SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
	{
		SetContext(context);
	}

	SceneHierarchyPanel::~SceneHierarchyPanel()
	{
		delete m_Context;
	}

	void SceneHierarchyPanel::SetContext(Scene* context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context };
			auto& tc = entity.GetComponent<TagComponent>();
			ImGui::Text("%s", tc.Tag.c_str());
		});
		//ImGui::ShowDemoWindow();
		ImGui::End();
	}
}