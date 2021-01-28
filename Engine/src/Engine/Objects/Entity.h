#pragma once

#include "Scene.h"

namespace Engine {

	class Entity
	{
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		//Entity(const Entity& other) = default;
		Entity(entt::entity id, Scene* scene);
		virtual ~Entity();

		virtual void Render(sf::RenderTarget& rt) {}
		virtual void Update(float& ts) {}


		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ENGINE_ASSERT(!HasComponent<T>(), "Entity already has such component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityId, std::forward<Args>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			ENGINE_ASSERT(HasComponent<T>(), "Entity does not have such component!");
			return m_Scene->m_Registry.get<T>(m_EntityId);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityId);
		}
		
		template<typename T>
		void RemoveComponent()
		{
			ENGINE_ASSERT(!HasComponent<T>(), "Entity does not have such component!");
			m_Scene->m_Registry.remove<T>(m_EntityId);
		}

		operator bool() const { return (int)m_EntityId != 0; }

		operator uint32_t() const { return (uint32_t)m_EntityId; };

	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityId{ entt::null };
		std::string m_Name;
	};

}