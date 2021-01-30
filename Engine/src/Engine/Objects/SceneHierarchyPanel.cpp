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
			ImGuiTreeNodeFlags flags = ((m_Selected == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			//ImGui::Text("%s", tc.Tag.c_str());
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tc.Tag.c_str());

			if (ImGui::IsItemClicked())
			{
				m_Selected = entity;
			}

		});

		//ImGui::ShowDemoWindow();
		//ImGui::ShowDemoWindow();
		ImGui::End();
	}
}