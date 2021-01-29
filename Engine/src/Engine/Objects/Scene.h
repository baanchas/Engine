#pragma once

namespace Engine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(std::string name);

		void OnUpdate(float& ts);
		void Render(sf::RenderTarget& rt);

		void OnScenePLay(float ts);

		inline size_t Count() const { return m_Registry.size(); }
	private:
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}
