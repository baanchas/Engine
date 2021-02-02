#pragma once

namespace Engine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(float& ts);
		void Render(sf::RenderTarget& rt);

		Entity* CreateEntity(std::string name);
		void DestroyEntity(Entity entity);

		void OnScenePLay(float ts);

		entt::registry& GetRegistry() { return m_Registry; };

		template<typename T>
		bool OnComponentAdded(Entity entity, T& component);

		inline size_t Count() const { return m_Registry.size(); }

		//Entity m_MainCamera;

		std::vector<Entity*> m_Entities;
	private:
		entt::registry m_Registry;
		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}
