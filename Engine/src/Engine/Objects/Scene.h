#pragma once

#include "Engine/Components/Components.h"


#include "entt.hpp"

namespace Engine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity();

		void OnUpdate(float& ts);
		void Render(sf::RenderTarget& rt);

		inline size_t Count() const { return m_Registry.size(); }
	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}
