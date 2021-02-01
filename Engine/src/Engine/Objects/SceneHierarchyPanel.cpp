#include "enpch.h"
#include "SceneHierarchyPanel.h"
#include "imgui_internal.h"


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
			ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tc.Tag.c_str());

			if (ImGui::IsItemClicked())
			{
				m_SelectedEntity = entity;
			}
			
			if (ImGui::BeginPopupContextItem(0, 1))
			{
				if (ImGui::MenuItem("Delete Entity"))
				{
					if (m_SelectedEntity == entity)
						m_SelectedEntity = {};
					m_Context->DestroyEntity(entity);
				}
				ImGui::EndPopup();
			}
		});
		
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				m_Context->CreateEntity("Empty Entity");
			}

			ImGui::EndPopup();
		}


		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectedEntity)
		{
			DrawComponents(m_SelectedEntity);

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("Add Component");

			if (ImGui::BeginPopup("Add Component"))
			{
				if (ImGui::MenuItem("Rectangle Component"))
				{
					m_SelectedEntity.AddComponent<RectangleCOmponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Color Component"))
				{
					m_SelectedEntity.AddComponent<ColorComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Camera Component"))
				{
					m_SelectedEntity.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}

		ImGui::End();
	}

	// Draw TreePoppedInterface

	static void DrawFloat2Control(const std::string& label, float values[2], float resetValue = 0.0F, float columnWidth = 100.f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());

		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 1.0f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f, 0.1f, 0.15, 1.0f });

		if (ImGui::Button("X", buttonSize))
			values[0] = resetValue;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values[0], 1.0f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.15, 1.0f });

		if (ImGui::Button("Y", buttonSize))
			values[1] = resetValue;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values[1], 1.0f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	static void DrawFloatControl(const std::string& label, float& value, float resetValue, float speed, float columnWidth = 100.f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());

		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		if (ImGui::Button("R", buttonSize))
			value = resetValue;

		ImGui::SameLine();
		ImGui::DragFloat("##R", &value, speed);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	// Draw Components

	ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(TagComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Tag");

			ImGui::SameLine(ImGui::GetWindowWidth() - 20.f);
			if (ImGui::Button("+", ImVec2(15, 15)))
			{
				ImGui::OpenPopup("Component settings");
			}
			bool removeComponent = false;

			if (ImGui::BeginPopup("Component settings"))
			{
				if (ImGui::MenuItem("Remove Component"))
				{
					removeComponent = true;
				}

				ImGui::EndPopup();
			}

			if (open)
			{

				auto& tag = entity.GetComponent<TagComponent>().Tag;

				ImGui::InputText("Tag", (char*)tag.c_str(), tag.capacity() + 1);

				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<TagComponent>();
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>();

				float* pos[2] = { &transform.Position.x, &transform.Position.y };
				float* scale[2] = { &transform.Scale.x, &transform.Scale.y };
				float* rotation = &transform.Rotation;

				DrawFloat2Control("Position", *pos);
				DrawFloat2Control("Scale", *scale, 1.0f);
				DrawFloatControl("Rotation", transform.Rotation, 0.0f, 1.0f);


				ImGui::TreePop();

			}
		}

		if (entity.HasComponent<ColorComponent>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(ColorComponent).hash_code(), treeFlags, "Color Component");

			ImGui::SameLine(ImGui::GetWindowWidth() - 20.f);
			if (ImGui::Button("+", ImVec2(15, 15)))
			{
				ImGui::OpenPopup("Component settings");
			}

			bool removeComponent = false;

			if (ImGui::BeginPopup("Component settings"))
			{
				if (ImGui::MenuItem("Remove Component"))
				{
					removeComponent = true;
				}

				ImGui::EndPopup();
			}

			if (open)
			{
				auto& cc = entity.GetComponent<ColorComponent>();

				colorBuffer[0] = (float)cc.Color.r / (float)255;
				colorBuffer[1] = (float)cc.Color.g / (float)255;
				colorBuffer[2] = (float)cc.Color.b / (float)255;

				ImGui::ColorEdit3("Change Color", colorBuffer, ImGuiColorEditFlags_InputRGB);

				cc.Color.r = colorBuffer[0] * 255;
				cc.Color.g = colorBuffer[1] * 255;
				cc.Color.b = colorBuffer[2] * 255;


				ImGui::TreePop();
			}

			if (removeComponent)
			{
				entity.RemoveComponent<ColorComponent>();
			}
			removeComponent = false;
		}

		if (entity.HasComponent<RectangleCOmponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(RectangleCOmponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Rectangle"))
			{
				auto& rc = entity.GetComponent<RectangleCOmponent>();

				float* size[2] = { &rc.Size.x, &rc.Size.y };

				DrawFloat2Control("Size", *size, 100.f);

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cc = entity.GetComponent<CameraComponent>();

				DrawFloatControl("Rotation", cc.Camera.m_zoomLevel, 1.0f, 0.01f);

				ImGui::TreePop();
			}
		}
	}

}